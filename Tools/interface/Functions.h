#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "TLorentzVector.h" 
#include "TMath.h"

#define PI 3.141592654

/** \file NumericalFunctions.h
 * \brief Some numerical functions
 * \author S. Narayanan
 */

//////////////////////////////////////////////////////////////////////////////////

/**
 * \param x	value to be cleaned
 * \param d	default value
 * \brief Returns a default value if input is NaN
 */
inline double clean(double x, double d=-1) {
	return TMath::Finite(x) ? x : d;
}

/**
 * \param val	input value
 * \param low	low value
 * \param high	high value
 * \brief Bounds a value within a range
 */
inline double bound(double val, double low, double high) {
	return TMath::Max(low,TMath::Min(high,val));
}

template <typename T>
inline int sign(T x) {
    return (x<0) ? -1 : 1;
}

// need a non-templated instance to be able to 
// load in interactive ROOT => use in TTreeFormula
inline int dsign(double x) {
    return sign(x);
}

/**
 * \brief Mass of a pair of particles
 */
inline double Mxx(double pt1, double eta1, double phi1, double m1, double pt2, double eta2, double phi2, double m2) {
    TLorentzVector v1,v2;
    v1.SetPtEtaPhiM(pt1,eta1,phi1,m1);
    v2.SetPtEtaPhiM(pt2,eta2,phi2,m2);
    return (v1+v2).M();
}

inline double MT(double pt1, double phi1, double pt2, double phi2)
{
    TLorentzVector v1,v2;
    v1.SetPtEtaPhiM(pt1,0,phi1,0);
    v2.SetPtEtaPhiM(pt2,0,phi2,0);
    return (v1+v2).M();
}

/**
 * \brief Signed delta-phi
 */
inline double SignedDeltaPhi(double phi1, double phi2) {
    double dPhi = phi1-phi2;
    if (dPhi<-PI)
        dPhi = 2*PI+dPhi;
    else if (dPhi>PI)
        dPhi = -2*PI+dPhi;
    return dPhi;
}

/**
 * \brief Calculates the delta-R-squared metric
 */
inline double DeltaR2(double eta1, double phi1, double eta2, double phi2) {
    float dEta2 = (eta1-eta2); dEta2 *= dEta2;
    float dPhi = SignedDeltaPhi(phi1,phi2);
    return dEta2 + dPhi*dPhi;
}

/**
 * \brief Exponential times erf, aka CMSShape
 */
inline double ExpErf(double x, double a, double b, double c) {
    double exp_ = TMath::Exp(c*x);
    double erf_ = TMath::Erf((x-a)/b);
    return exp_*(1+erf_)/2;
}

#endif
