#ifndef _matrix_h_
#define _matrix_h_
#include "vector.h"
#include <array>


typedef std::array< std::array<float, 3>, 3 > NozMatrix3;
typedef std::array< std::array<float, 4>, 4 > NozMatrix;

/// NOZ MATRIX 4*4
inline void NozM4Idendity(NozMatrix &mout)
{
    mout[0][0] = 1.0;
    mout[0][1] = 0.0;
    mout[0][2] = 0.0;
    mout[0][3] = 0.0;

    mout[1][0] = 0.0;
    mout[1][1] = 1.0;
    mout[1][2] = 0.0;
    mout[1][3] = 0.0;

    mout[2][0] = 0.0;
    mout[2][1] = 0.0;
    mout[2][2] = 1.0;
    mout[2][3] = 0.0;

    mout[3][0] = 0.0;
    mout[3][1] = 0.0;
    mout[3][2] = 0.0;
    mout[3][3] = 1.0;
}

inline NozMatrix getNozM4Identity() {
    NozMatrix identityMat;
    NozM4Idendity(identityMat);
    return identityMat;
}




inline void nozMatrix_set(NozMatrix &mout,
                          double r00, double r01, double r02, double r03,
                          double r10, double r11, double r12, double r13,
                          double r20, double r21, double r22, double r23,
                          double r30, double r31, double r32, double r33)
{
    mout[0][0] = r00;     mout[0][1] = r01;     mout[0][2] = r02;     mout[0][3] = r03;
    mout[1][0] = r10;     mout[1][1] = r11;     mout[1][2] = r12;     mout[1][3] = r13;
    mout[2][0] = r20;     mout[2][1] = r21;     mout[2][2] = r22;     mout[2][3] = r23;
    mout[3][0] = r30;     mout[3][1] = r31;     mout[3][2] = r32;     mout[3][3] = r33;
}



inline void NozM4PointByMatrixMult(NozPoint &pout, const NozMatrix &mat, const NozPoint pin)
{
    pout.x = mat[0][0] * pin.x + mat[1][0] * pin.y + mat[2][0] * pin.z + mat[3][0];// * 1.0;
    pout.y = mat[0][1] * pin.x + mat[1][1] * pin.y + mat[2][1] * pin.z + mat[3][1];// * 1.0;
    pout.z = mat[0][2] * pin.x + mat[1][2] * pin.y + mat[2][2] * pin.z + mat[3][2];// * 1.0;
}


inline NozPoint getNozPointByMatrixMult(const NozMatrix &mat, const NozPoint &pin) {
    NozPoint pout;
    NozM4PointByMatrixMult(pout, mat, pin);
    return pout;
}


inline void NozM4VecByMatrixMult(NozVector &vout, const NozMatrix &mat, const NozVector vin)
{

    vout.x = mat[0][0] * vin.x + mat[1][0] * vin.y + mat[2][0] * vin.z;// + mat[3][0] * 0.0;
    vout.y = mat[0][1] * vin.x + mat[1][1] * vin.y + mat[2][1] * vin.z;// + mat[3][1] * 0.0;
    vout.z = mat[0][2] * vin.x + mat[1][2] * vin.y + mat[2][2] * vin.z;// + mat[3][2] * 0.0;
}


inline NozVector getNozVecByMatrixMult(const NozMatrix &mat, const NozVector &vin) {
    NozVector vout;
    NozM4VecByMatrixMult(vout, mat, vin);
    return vout;
}


//inline const NozVector operator*(const NozMatrix& m, const NozVector& v)
//{
//    return getNozVecByMatrixMult(m, v);
//
//}


inline void NozM3VecByMatrixMult(NozVector &vout, const NozMatrix3 &mat, const NozVector vin)
{

    vout.x = mat[0][0] * vin.x + mat[1][0] * vin.y + mat[2][0] * vin.z;// + mat[3][0] * 0.0;
    vout.y = mat[0][1] * vin.x + mat[1][1] * vin.y + mat[2][1] * vin.z;// + mat[3][1] * 0.0;
    vout.z = mat[0][2] * vin.x + mat[1][2] * vin.y + mat[2][2] * vin.z;// + mat[3][2] * 0.0;
}

inline void NozM4RotationXYZ(const NozVector &up,  const double alpha, NozMatrix &mout)
{
    const NozVector normalUp = NozVecNormalize(up);
    double c = cos(alpha);
    double s = sin(alpha);
    
    mout[0][0] = normalUp.x*normalUp.x * (1 - c) + c;
    mout[0][1] = normalUp.x*normalUp.y * (1 - c) - normalUp.z*s;
    mout[0][2] = normalUp.x*normalUp.z * (1 - c) + normalUp.y*s;
    mout[0][3] = 0.0;

    mout[1][0] = normalUp.x*normalUp.y * (1 - c) + normalUp.z*s;
    mout[1][1] = normalUp.y*normalUp.y * (1 - c) + c;
    mout[1][2] = normalUp.y*normalUp.z * (1 - c) - normalUp.x*s;
    mout[1][3] = 0.0;

    mout[2][0] = normalUp.x*normalUp.z * (1 - c) - normalUp.y*s;
    mout[2][1] = normalUp.y*normalUp.z * (1 - c) + normalUp.x*s;
    mout[2][2] = normalUp.z*normalUp.z * (1 - c) + c;
    mout[2][3] = 0.0;

    mout[3][0] = 0.0;
    mout[3][1] = 0.0;
    mout[3][2] = 0.0;
    mout[3][3] = 1.0;
}


/// NOZ MATRIX 3*3
inline void NozM3Idendity(NozMatrix3 &mout){
    mout[0][0] = 1.0;   mout[0][1] = 0.0;   mout[0][2] = 0.0;
    mout[1][0] = 0.0;   mout[1][1] = 1.0;    mout[1][2] = 0.0;
    mout[2][0] = 0.0;    mout[2][1] = 0.0;    mout[2][2] = 1.0;
}

inline void nozMatrix3_set(NozMatrix3 &mout,
                            const double &r00, const double &r01, const double &r02,
                            const double &r10, const double &r11, const double &r12,
                            const double &r20, const double &r21, const double &r22)
{
    mout[0][0] = r00;     mout[0][1] = r01;     mout[0][2] = r02;
    mout[1][0] = r10;     mout[1][1] = r11;     mout[1][2] = r12; 
    mout[2][0] = r20;     mout[2][1] = r21;     mout[2][2] = r22;

}


inline double nozMat3GetDeterminant(const NozMatrix3 &a){

    //a00 * (a22 * a11 - a12 * a21) + a01 * (-a22 * a10 + a12 * a20) + a02 * (a21 * a10 - a11 * a20);

    return a[0][0] * (a[2][2] * a[1][1] - a[1][2] * a[2][1]) + a[0][1] * (-a[2][2] * a[1][0] + a[1][2] * a[2][0]) + a[0][2] * (a[2][1] * a[1][0] - a[1][1] * a[2][0]);

}



inline void nozMat4inverse(const NozMatrix &min, NozMatrix &FloatResult)
{
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //
    NozMatrix Result;
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
    /* transpose matrix */
    for (size_t i = 0; i < 4; i++)
    {
        src[i + 0 ] = min[i][0];
        src[i + 4 ] = min[i][1];
        src[i + 8 ] = min[i][2];
        src[i + 12] = min[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    Result[0][0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
    Result[0][0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
    Result[0][1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
    Result[0][1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
    Result[0][2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
    Result[0][2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
    Result[0][3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
    Result[0][3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
    Result[1][0] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
    Result[1][0] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
    Result[1][1] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
    Result[1][1] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
    Result[1][2] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
    Result[1][2] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
    Result[1][3] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
    Result[1][3] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2]*src[7];
    tmp[1] = src[3]*src[6];
    tmp[2] = src[1]*src[7];
    tmp[3] = src[3]*src[5];
    tmp[4] = src[1]*src[6];
    tmp[5] = src[2]*src[5];

    tmp[6] = src[0]*src[7];
    tmp[7] = src[3]*src[4];
    tmp[8] = src[0]*src[6];
    tmp[9] = src[2]*src[4];
    tmp[10] = src[0]*src[5];
    tmp[11] = src[1]*src[4];
    /* calculate second 8 elements (cofactors) */
    Result[2][0] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
    Result[2][0] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
    Result[2][1] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
    Result[2][1] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
    Result[2][2] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
    Result[2][2] -= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
    Result[2][3] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
    Result[2][3] -= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
    Result[3][0] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
    Result[3][0] -= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
    Result[3][1] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
    Result[3][1] -= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
    Result[3][2] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
    Result[3][2] -= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
    Result[3][3] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
    Result[3][3] -= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
    /* calculate determinant */
    det=src[0]*Result[0][0]+src[1]*Result[0][1]+src[2]*Result[0][2]+src[3]*Result[0][3];
    /* calculate matrix inverse */
    det = 1.0f / det;


    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            FloatResult[i][j] = float(Result[i][j] * det);
        }
    }
    
}


inline void NozM4_MatrixByMatrixMult(const NozMatrix &A, const NozMatrix &B, NozMatrix &Result)
{

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t i2 = 0; i2 < 4; i2++)
        {
            float Total = 0.0f;
            for (size_t i3 = 0; i3 < 4; i3++)
            {
                Total += A[i][i3] * B[i3][i2];
            }
            Result[i][i2] = Total;
        }
    }
}

#endif