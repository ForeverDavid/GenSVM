/**
 * @file gensvm_update.h
 * @author Gertjan van den Burg
 * @date 2016-10-14
 * @brief Header file for gensvm_update.c

 * Copyright (C)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 */

#ifndef GENSVM_UPDATE_H
#define GENSVM_UPDATE_H

#include "gensvm_base.h"
#include "gensvm_print.h"

// function declarations
double gensvm_calculate_omega(struct GenModel *model, struct GenData *data,
		long i);
bool gensvm_majorize_is_simple(struct GenModel *model, struct GenData *data,
		long i);
void gensvm_calculate_ab_non_simple(struct GenModel *model, long i, long j,
		double *a, double *b_aq);
void gensvm_calculate_ab_simple(struct GenModel *model, long i, long j,
		double *a, double *b_aq);
double gensvm_get_alpha_beta(struct GenModel *model, struct GenData *data,
		long i, double *beta);
void gensvm_get_update(struct GenModel *model, struct GenData *data, 
		struct GenWork *work);
void gensvm_get_ZAZ_ZB_dense(struct GenModel *model, struct GenData *data,
		struct GenWork *work);
void gensvm_get_ZAZ_ZB_sparse(struct GenModel *model, struct GenData *data,
		struct GenWork *work);
void gensvm_get_ZAZ_ZB(struct GenModel *model, struct GenData *data, 
		struct GenWork *work);
int dposv(char UPLO, int N, int NRHS, double *A, int LDA, double *B,
		int LDB);
int dsysv(char UPLO, int N, int NRHS, double *A, int LDA, int *IPIV,
		double *B, int LDB, double *WORK, int LWORK);

#endif
