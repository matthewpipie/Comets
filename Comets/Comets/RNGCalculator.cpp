/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "RNGCalculator.h"

double RNGCalculator::randomDouble(double min, double max) {
	return (max - min)
		* (static_cast<double>(rand()) / static_cast<double>(RAND_MAX))
		+ min;
}

