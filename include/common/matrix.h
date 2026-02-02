#ifndef _matrix_h_
#define _matrix_h_
#include "vector.h"
#include <array>


typedef std::array< std::array<float, 3>, 3 > NozMatrix3;
typedef std::array< std::array<float, 4>, 4 > NozMatrix;


// FOR FLIPPING Z AXIS (RH to LH or LH to RH)
static const NozMatrix ZFlip = { {
  {{ 1, 0,  0, 0 }},
  {{ 0, 1,  0, 0 }},
  {{ 0, 0, -1, 0 }},
  {{ 0, 0,  0, 1 }},
} };

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

inline bool isNozM4Identity(const NozMatrix& m, float eps = 1e-6f) {
    NozMatrix identityMat;
    NozM4Idendity(identityMat);

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k)
            if (fabsf(identityMat[i][k] - m[i][k]) > eps)
                return false;
    }


    return true;
}

inline void nozMatrix_set(NozMatrix &mout,
                          float r00, float r01, float r02, float r03,
    float r10, float r11, float r12, float r13,
    float r20, float r21, float r22, float r23,
    float r30, float r31, float r32, float r33)
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

inline void NozM4RotationXYZ(const NozVector &up,  const float alpha, NozMatrix &mout)
{
    const NozVector normalUp = NozVecNormalize(up);
    float c = cos(alpha);
    float s = sin(alpha);
    
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
                            const float& r00, const float& r01, const float& r02,
                            const float& r10, const float& r11, const float& r12,
                            const float& r20, const float& r21, const float& r22)
{
    mout[0][0] = r00;     mout[0][1] = r01;     mout[0][2] = r02;
    mout[1][0] = r10;     mout[1][1] = r11;     mout[1][2] = r12; 
    mout[2][0] = r20;     mout[2][1] = r21;     mout[2][2] = r22;

}


inline double nozMat3GetDeterminant(const NozMatrix3 &a){

    //a00 * (a22 * a11 - a12 * a21) + a01 * (-a22 * a10 + a12 * a20) + a02 * (a21 * a10 - a11 * a20);

    return a[0][0] * (a[2][2] * a[1][1] - a[1][2] * a[2][1]) + a[0][1] * (-a[2][2] * a[1][0] + a[1][2] * a[2][0]) + a[0][2] * (a[2][1] * a[1][0] - a[1][1] * a[2][0]);

}

inline void nozMat4gjInverse(const NozMatrix& m, NozMatrix& out)
{
    // Gauss–Jordan elimination with partial pivoting on [m | I]
    // Works with row-major NozMatrix and avoids NaNs on near-singular inputs.

    // Augmented matrix: 4 rows, 8 cols  => [m | I]
    float a[4][8];
    for (int r = 0; r < 4; ++r) {
        a[r][0] = m[r][0]; a[r][1] = m[r][1]; a[r][2] = m[r][2]; a[r][3] = m[r][3];
        a[r][4] = (r == 0) ? 1.f : 0.f;
        a[r][5] = (r == 1) ? 1.f : 0.f;
        a[r][6] = (r == 2) ? 1.f : 0.f;
        a[r][7] = (r == 3) ? 1.f : 0.f;
    }

    // Forward elimination
    for (int col = 0; col < 4; ++col) {
        // Find pivot row
        int pivot = col;
        float maxAbs = fabsf(a[col][col]);
        for (int r = col + 1; r < 4; ++r) {
            float v = fabsf(a[r][col]);
            if (v > maxAbs) { maxAbs = v; pivot = r; }
        }

        // Singular / nearly singular: return identity to avoid NaNs
        if (maxAbs < NOZ_EPSILON) {
            throw std::invalid_argument("Cannot invert singular matrix.");
            NozM4Idendity(out);
            return;
        }

        // Swap current row with pivot row
        if (pivot != col) {
            for (int c = 0; c < 8; ++c) std::swap(a[col][c], a[pivot][c]);
        }

        // Normalize pivot row
        float invPivot = 1.0f / a[col][col];
        for (int c = 0; c < 8; ++c) a[col][c] *= invPivot;

        // Eliminate this column in other rows
        for (int r = 0; r < 4; ++r) {
            if (r == col) continue;
            float f = a[r][col];
            if (f != 0.0f) {
                for (int c = 0; c < 8; ++c) a[r][c] -= f * a[col][c];
            }
        }
    }

    // Extract inverse from augmented matrix
    for (int r = 0; r < 4; ++r) {
        out[r][0] = a[r][4];
        out[r][1] = a[r][5];
        out[r][2] = a[r][6];
        out[r][3] = a[r][7];
    }
}


inline void nozMat4inverse(const NozMatrix &min, NozMatrix &FloatResult)
{
    if (min[0][3] != 0 || min[1][3] != 0 || min[2][3] != 0 || min[3][3] != 1) {
        nozMat4gjInverse(min, FloatResult);
        return;
    }

    FloatResult = { {
        {{
        min[1][1] * min[2][2] - min[2][1] * min[1][2],
        min[2][1] * min[0][2] - min[0][1] * min[2][2],
        min[0][1] * min[1][2] - min[1][1] * min[0][2],
        0
        }},
        {{
        min[2][0] * min[1][2] - min[1][0] * min[2][2],
        min[0][0] * min[2][2] - min[2][0] * min[0][2],
        min[1][0] * min[0][2] - min[0][0] * min[1][2],
        0 }},
        {{
        min[1][0] * min[2][1] - min[2][0] * min[1][1],
        min[2][0] * min[0][1] - min[0][0] * min[2][1],
        min[0][0] * min[1][1] - min[1][0] * min[0][1],
        0}},
        {{ 0, 0, 0, 1 }},
        } };

    float r = min[0][0] * FloatResult[0][0] + min[0][1] * FloatResult[1][0] + min[0][2] * FloatResult[2][0];

    if (fabsf(r) >= 1) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                FloatResult[i][j] /= r;
            }
        }
    }
    else {
        float mr = fabsf(r) / std::numeric_limits<float>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (mr > fabsf(FloatResult[i][j])) {
                    FloatResult[i][j] /= r;
                }
                else {
                    throw std::invalid_argument("Cannot invert singular matrix.");
                    FloatResult = NozMatrix();
                    return;
                }
            }
        }
    }

    FloatResult[3][0] = -min[3][0] * FloatResult[0][0] - min[3][1] * FloatResult[1][0] - min[3][2] * FloatResult[2][0];
    FloatResult[3][1] = -min[3][0] * FloatResult[0][1] - min[3][1] * FloatResult[1][1] - min[3][2] * FloatResult[2][1];
    FloatResult[3][2] = -min[3][0] * FloatResult[0][2] - min[3][1] * FloatResult[1][2] - min[3][2] * FloatResult[2][2];

}



inline void NozM4_MatrixByMatrixMult(const NozMatrix& A, const NozMatrix& B, NozMatrix& Result)
{
    NozMatrix tmp;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            float total = 0.0f;
            for (size_t k = 0; k < 4; k++) {
                total += A[i][k] * B[k][j];
            }
            tmp[i][j] = total;
        }
    }
    Result = tmp;
}

inline void NozM4Transpose3x3(const NozMatrix& m, NozMatrix& out)
{
    // start from identity to preserve [0 0 0 1] and zero translations
    NozM4Idendity(out);


    // transpose the 3x3 rotational/reflection block
    out[0][0] = m[0][0]; out[0][1] = m[1][0]; out[0][2] = m[2][0];
    out[1][0] = m[0][1]; out[1][1] = m[1][1]; out[1][2] = m[2][1];
    out[2][0] = m[0][2]; out[2][1] = m[1][2]; out[2][2] = m[2][2];
}


inline void NozM4HandnessAxisMatrix(int handness, int upAxis, NozMatrix& mout)
{
    NozM4Idendity(mout);
    if (upAxis == 2) {
        NozMatrix rot = getNozM4Identity();
        rot[0][0] = 1.0f;  rot[0][1] = 0.0f;  rot[0][2] = 0.0f;
        rot[1][0] = 0.0f;  rot[1][1] = 0.0f;  rot[1][2] = -1.0f;
        rot[2][0] = 0.0f;  rot[2][1] = 1.0f; rot[2][2] = 0.0f;
        NozM4_MatrixByMatrixMult(rot, mout, mout);
    }
    else if (upAxis == 0) {
        NozMatrix rot = getNozM4Identity();
        rot[0][0] = 0.0f; rot[0][1] = -1.0f;
        rot[1][0] = 1.0f; rot[1][1] = 0.0f;
        NozM4_MatrixByMatrixMult(rot, mout, mout);
    }
    if (handness == 1) {
        NozMatrix flip = getNozM4Identity();
        flip[2][2] = -1.0f;
        NozM4_MatrixByMatrixMult(mout, flip, mout);
    }
}


#endif