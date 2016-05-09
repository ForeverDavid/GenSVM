/**
 * @file gensvm_pred.c
 * @author Gertjan van den Burg
 * @date August 9, 2013
 * @brief Main functions for predicting class labels..
 *
 * @details
 * This file contains functions for predicting the class labels of instances
 * and a function for calculating the predictive performance (hitrate) of
 * a prediction given true class labels.
 *
 */

#include <cblas.h>
#include <math.h>

#include "libGenSVM.h"
#include "gensvm.h"
#include "gensvm_kernel.h"
#include "gensvm_matrix.h"
#include "gensvm_pred.h"

/**
 * @brief Predict class labels of data given and output in predy
 *
 * @details
 * The labels are predicted by mapping each instance in data to the
 * simplex space using the matrix V in the given model. Next, for each
 * instance the nearest simplex vertex is determined using an Euclidean
 * norm. The nearest simplex vertex determines the predicted class label,
 * which is recorded in predy.
 *
 * @param[in] 	data 		GenData to predict labels for
 * @param[in] 	model 		GenModel with optimized V
 * @param[out] 	predy 		pre-allocated vector to record predictions in
 */
void gensvm_predict_labels(struct GenData *testdata, struct GenModel *model,
		long *predy)
{
	long i, j, k, n, m, K, label;
	double norm, min_dist, *S, *ZV, *U;

	n = testdata->n;
	m = testdata->r;
	K = model->K;

	// allocate necessary memory
	S = Calloc(double, K-1);
	ZV = Calloc(double, n*(K-1));
	U = Calloc(double, K*(K-1));

	// Generate the simplex matrix
	gensvm_simplex_gen(K, U);

	// Generate the simplex space vectors
	cblas_dgemm(
			CblasRowMajor,
			CblasNoTrans,
			CblasNoTrans,
			n,
			K-1,
			m+1,
			1.0,
			testdata->Z,
			m+1,
			model->V,
			K-1,
			0.0,
			ZV,
			K-1);

	// Calculate the distance to each of the vertices of the simplex.
	// The closest vertex defines the class label
	for (i=0; i<n; i++) {
		label = 0;
		min_dist = INFINITY;
		for (j=0; j<K; j++) {
			for (k=0; k<K-1; k++) {
				S[k] = matrix_get(ZV, K-1, i, k) -
					matrix_get(U, K-1, j, k);
			}
			norm = cblas_dnrm2(K-1, S, 1);
			if (norm < min_dist) {
				label = j+1;
				min_dist = norm;
			}
		}
		predy[i] = label;
	}

	free(ZV);
	free(U);
	free(S);
}

/**
 * @brief Calculate the predictive performance (percentage correct)
 *
 * @details
 * The predictive performance is calculated by simply counting the number
 * of correctly classified samples and dividing by the total number of
 * samples, multiplying by 100.
 *
 * @param[in] 	data 	the GenData dataset with known labels
 * @param[in] 	predy 	the predicted class labels
 *
 * @returns percentage correctly classified.
 */
double gensvm_prediction_perf(struct GenData *data, long *predy)
{
	long i, correct = 0;
	double performance;

	for (i=0; i<data->n; i++)
		if (data->y[i] == predy[i])
			correct++;

	performance = ((double) correct)/((double) data->n)* 100.0;

	return performance;
}
