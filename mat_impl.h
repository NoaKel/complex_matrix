#ifndef _MAT_IMPL_H
#define _MAT_IMPL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;


/* *****************************************************
Function: Mat C'tor
Abstract: Creates a new empty matrix, width w
Parameters: 
w - width of the created matrix
Return Value: N/A
***************************************************** */
template <class T>
Mat<T>::Mat(unsigned int w):
Vec<T>() 
{
 w_=w;
	if (w < 1) 
	{
		ExceptionEmptyOperand EEO;
		throw EEO;
	};
}

/* *****************************************************
Function: Mat C'tor
Abstract: Creates 1-by-n Matrix, with the given vector
Parameters:
vec_1d - Only line of the matrix
Return Value: N/A
***************************************************** */
template <class T>
Mat<T>::Mat(Vec<T> vec_1d ):
Vec<Vec<T>>(vec_1d)
 {
	w_ = vec_1d.size();
	if (w_ < 1)
	{
		ExceptionEmptyOperand EEO;
		throw EEO;
	}
}

/* *****************************************************
Function: Mat C'tor
Abstract: Creates a new matrix, from 2d-vector
Parameters:
vec_2d - vector containing the matrix's lines
Return Value: N/A
***************************************************** */
template <class T>
Mat<T>::Mat(Vec< Vec<T> > vec_2d):
Vec<Vec<T>>(vec_2d)
 {
	w_ = vec_2d[0].size();
	if (w_ < 1)
	{
		ExceptionEmptyOperand EEO;
		throw EEO;
	};

	for (typename list<Vec<T>>::const_iterator itr = vec_2d.begin(); itr != vec_2d.end(); ++itr) 
	{
		if (w_!= (*itr).size())
		{
			ExceptionWrongDimensions EWD;
			throw EWD;
		};
	}
}

/* *****************************************************
Function: width
Abstract: returns the width of the matrix
Parameters:
Return Value: matrix's width
***************************************************** */
template <class T>
unsigned int Mat<T>::width() const {
	return w_;
}

/* *****************************************************
Function: height
Abstract: returns the height of the matrix
Parameters:
Return Value: matrix's height
***************************************************** */
template <class T>
unsigned int Mat<T>::height() const {
	return (*this).vals_.size();
}

/* *****************************************************
Function: operator+
Abstract: adds a matrix, with the same dimensions
Parameters:
rhs - reference to the added matrix
Return Value: matrices addition result
***************************************************** */
template <class T>
Mat<T> Mat<T>::operator+(const Mat& rhs) const {
	if ((rhs.height() != (*this).vals_.size()) || (rhs.width() != w_)) {
		ExceptionWrongDimensions EWD;
		throw EWD;
	}
	Vec<Vec<T>> new_mat;
	typename list<Vec<T>>::const_iterator add_mat_itr = rhs.begin();
	for (typename list<Vec<T>>::const_iterator itr = (*this).vals_.begin(); itr != (*this).vals_.end(); ++itr) {
		new_mat.push_back((*itr) + (*add_mat_itr));
		add_mat_itr++;
	}
	return Mat(new_mat);
}

/* *****************************************************
Function: operator*
Abstract: multiply the matrix by a (right) scalar
Parameters:
rhs - reference to the scalar
Return Value: matrix multiplied by a scalar
***************************************************** */
template <class T>
Mat<T> Mat<T>::operator*(const T& rhs) const {
	Vec<Vec<T>> new_mat;
	for (typename list<Vec<T>>::const_iterator itr = (*this).vals_.begin(); itr != (*this).vals_.end(); ++itr) {
		Vec<T> tmp = rhs*(*itr);
		new_mat.push_back(tmp);
	}
	return Mat(new_mat);
}

/* *****************************************************
Function: operator*
Abstract: matrecis multiplation
Parameters:
rhs - reference to the right-side matrix
Return Value: matrices multiplation result
***************************************************** */
template <class T>
Mat<T> Mat<T>::operator*(const Mat<T>& rhs) const {
	/*To simplify the implementation of a*b , we are working on trans(b) rows 
	and calculating the result matrix's rows*/
	if (rhs.height() != w_) {
		ExceptionWrongDimensions EWD;
		throw EWD;
	}
	Mat<T> Trhs = rhs.transpose(); 
	Vec<Vec<T>> new_mat;
	for (typename list<Vec<T>>::const_iterator itrL = (*this).vals_.begin(); itrL != (*this).vals_.end(); ++itrL) {
		Vec<T> tmp_vec;
		for (typename list<Vec<T>>::const_iterator itrR = Trhs.begin(); itrR != Trhs.end(); ++itrR) {
			T tmp_val=0;
			for (unsigned int i = 0; i != w_; i++) {
				T sum= (*itrL)[i]*(*itrR)[i];
				tmp_val = tmp_val + sum;
			}
			tmp_vec.push_back(tmp_val);
		}
		new_mat.push_back(tmp_vec);
	}
	return Mat(new_mat);
}

/* *****************************************************
Function: operator,
Abstract: concatenation of another matrix, from below
Parameters:
rhs - reference to the second matrix
Return Value: matrices concatention result
***************************************************** */
template <class T>
Mat<T> Mat<T>::operator,(const Mat<T>& rhs) const {
	if (rhs.width() != w_) {
		ExceptionWrongDimensions EWD;
		throw EWD;
	}
	Vec<Vec<T>> new_vec_2d;
	for (typename list<Vec<T>>::const_iterator itr = (*this).vals_.begin(); itr != (*this).vals_.end(); ++itr) {
		new_vec_2d.push_back(*itr);
	}
	for (typename list<Vec<T>>::const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr) {
		new_vec_2d.push_back(*itr);
	}
	Mat<T> new_mat = Mat(new_vec_2d);
	return new_mat;
}

/* *****************************************************
Function: get_rows
Abstract: rows of the matrix, in specified indeces
Parameters:
ind - vector of the indeces
Return Value: matrix of the specific rows
***************************************************** */
template <class T>
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const {
	Vec<Vec<T>> new_mat;
	for (list<unsigned int>::const_iterator itr = ind.begin(); itr != ind.end(); ++itr) {
		unsigned int idx = *itr;
		if ((idx<0) || (idx>((*this).vals_.size()-1))) 
		{
			ExceptionIndexExceed EIE;
			throw EIE;
		}
		Vec<T> tmp_vec = *next((*this).vals_.begin(), idx);
		new_mat.push_back(tmp_vec);
	}
	return Mat(new_mat);
}

/* *****************************************************
Function: get_cols
Abstract: columns of the matrix, in specified indeces
Parameters:
ind - vector of the indeces
Return Value: matrix of the specific columns
***************************************************** */
template <class T>
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const {
	/*making a copy of the matrix, and getting the ROWS of trans(mat)*/
	Mat<T> cpy = *this;
	Mat<T> t_cpy = cpy.transpose();
	Mat<T> t_res = t_cpy.get_rows(ind);
	return (t_res.transpose());
}

/* *****************************************************
Function: transpose
Abstract: transposing the matrix
Parameters: N/A
Return Value: a transposed matrix
***************************************************** */
template <class T>
Mat<T> Mat<T>::transpose() const {
	Vec<Vec<T>> new_mat;
	for (unsigned int n = 0; n != w_; n++) {
		Vec<T> tmp_vec;
		for (typename list<Vec<T>>::const_iterator itr = (*this).vals_.begin(); itr != (*this).vals_.end(); ++itr) {
			T tmp_val = (*itr)[n];
			tmp_vec.push_back(tmp_val);
		}
		new_mat.push_back(tmp_vec);
	}
	return Mat(new_mat);
}

/* *****************************************************
Function: operator*
Abstract: multiply the matrix by a (right) scalar
Parameters:
rhs - reference to the scalar
Return Value: matrix multiplied by a scalar
***************************************************** */
template <class T>
Mat<T> operator*(const T& lhs, const Mat<T>& rhs) {
	Mat<T> result_mat =rhs*lhs;
	return result_mat;
}

/* *****************************************************
Function: operator<<
Abstract: prints matrix
Parameters:
ro - ostream
v - reference to the matrix
Return Value: N/A
***************************************************** */
template <class T>
ostream& operator<<(ostream& ro, const Mat<T>& m) {
	ro << "(" << endl;
	for (typename list<Vec<T>>::const_iterator itr = m.begin(); itr != m.end(); ++itr) {
		if (itr == std::next(m.begin(), m.height() - 1))
			ro << *itr << endl;
		else
			ro << *itr << "," << endl;
	}
	ro << ")";
	return ro;
}

#endif
