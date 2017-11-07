#ifndef _SQ_MAT_IMPL_H
#define _SQ_MAT_IMPL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>


using std::cout;
using std::endl;

template <class T>
SqMat<T>::SqMat(Mat<T> m):
	Mat<T>(m)
{
	if (m.height() != m.width()) {
		ExceptionWrongDimensions EWD;
		throw EWD;
	}
}

template <class T>
unsigned int SqMat<T>::size() const {
	return (*this).w_;
}

template <class T>
T SqMat<T>::determinant() const {
	SqMat<T> cpy= *this;
	T det = 0;
	T mul = 1;
	T minusOne = -1;
	if ((*this).w_ == 1) 
	{
		Vec<T> v = *(*this).vals_.begin();
		det = v[0];
		return (det);
	}
	Vec<T> top_vec = *(*this).vals_.begin();
	Mat<T> down_mat = cpy.get_rows(range((unsigned int)1, (*this).w_ - 1));
	for (unsigned int i = 0; i < (*this).w_; ++i) {
		Vec<unsigned int> indices_vec = (range((unsigned int)0, i), range(i + 1, (*this).w_ - 1 - i));
		SqMat<T> minor_mat = down_mat.get_cols(indices_vec);
		det = det + top_vec[i] * mul*minor_mat.determinant();
		mul = minusOne*mul;
	}
	return det;

}

#endif