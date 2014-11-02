#ifndef MATOP_H
#define MATOP_H

#include <Rcpp.h>

class MatOp
{
protected:
    // Dimension of matrix
    // m rows and n columns
    // In eigenvalue problems, they are assumed to be the same,
    // and only n is used.
    int m;
    int n;
    // Shift parameters
    double sigmar;
    double sigmai;
    // Whether this matrix supports transpose product
    // Only used in SVD
    bool canTprod;
    // Whether this matrix supports shiftSolve()
    // Used in eigenvalue problems, when sigma is used
    bool canSolve;
public:
    // Constructor
    MatOp(int m_, int n_, double sigmar_, double sigmai_,
          bool canTprod_, bool canSolve_) :
        m(m_), n(n_), sigmar(sigmar_), sigmai(sigmai_),
        canTprod(canTprod_), canSolve(canSolve_)
    {}
    // y_out = A * x_in
    virtual void prod(double *x_in, double *y_out) = 0;
    // y_out = A' * x_in
    virtual void tprod(double *x_in, double *y_out)
    {
        if(!canTprod)
            Rcpp::stop("this matrix does not support transpose product");
    }
    // y_out = inv(A - sigma * I) * x_in
    virtual void shiftSolve(double *x_in, double *y_out)
    {
        if(!canSolve)
            Rcpp::stop("this matrix does not support solving linear equation");
    }
    double getsigmar() { return sigmar; }
    double getsigmai() { return sigmai; }
    // Destructor
    virtual ~MatOp() {}
};


#endif // MATOP_H
