#ifndef _color_h_
#define _color_h_

#include "constant.h"
#include "types.h"

/** \defgroup NOZ_RGBA Color API
* \brief
* This module contains color types and utilities.
* \{
*/

/** \name Constants
* \{
*/
/// CIE value X
#define CIE_X 0.95045593f;
/// CIE value Y
#define CIE_Y 1.f;
/// CIE value Z
#define CIE_Z 1.08905775f;

/*\}*/


/**
* LAB color
*/
struct NozLAB
{
/// lightness
    float l;
/// green-red	
    float a;
/// blue-yellow
	float b;
/// Minus operator
    NozLAB operator-(const NozLAB& lab) const
    {
        NozLAB temp;
        temp.l = l - lab.l;
        temp.a = a - lab.a;
        temp.b = b - lab.b;
        return temp;
    }
/// Minus operator
    NozLAB& operator-=(const NozLAB& lab)
    {
        l -= lab.l;
        a -= lab.a;
        b -= lab.b;
        return *this;
    }

};


/**
* xyY color
*/
struct NozxyY
{
/// x	
    float x;
/// y	
	float y;
/// Y	
	float	Y;
    NozxyY()
    {
        x = 0.0;
        y = 0.0;
        Y = 0.0;
    }
	/// 3 floats to xyY
    NozxyY(float x, float y, float Y)
    {
        this->x = x;
        this->y = y;
        this->Y = Y;
    }
};

/**
* RGB color
*/
struct NozRGB
{
/// red	
    float r;
/// green	
	float g; 
/// blue	
	float b;
    NozRGB()
    {
        r = 0.0; 
        g = 0.0; 
        b = 0.0;
    }
/// 3 floats to RGB    
    NozRGB(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
/// add operator
    NozRGB operator+(const NozRGB& rgb) const
    {
        NozRGB temp;
        temp.r = r + rgb.r;
        temp.g = g + rgb.g;
        temp.b = b + rgb.b;
        return temp;
    }
/// add operator
    NozRGB& operator+=(const NozRGB& rgb)
    {
        r += rgb.r;
        g += rgb.g;
        b += rgb.b;
        return *this;
    }
/// add operator
    NozRGB operator+(float f) const
    {
        NozRGB temp;
        temp.r = r + f;
        temp.g = g + f;
        temp.b = b + f;
        return temp;
    }
/// add operator
    NozRGB& operator+=(float f)
    {
        r += f;
        g += f;
        b += f;
        return *this;
    }
/// minus operator
    NozRGB operator-(const NozRGB& rgb) const
    {
        NozRGB temp;
        temp.r = r - rgb.r;
        temp.g = g - rgb.g;
        temp.b = b - rgb.b;
        return temp;
    }
/// minus operator
    NozRGB& operator-=(const NozRGB& rgb)
    {
        r -= rgb.r;
        g -= rgb.g;
        b -= rgb.b;
        return *this;
    }
/// minus operator
    NozRGB operator-(float f) const
    {
        NozRGB temp;
        temp.r = r - f;
        temp.g = g - f;
        temp.b = b - f;
        return temp;
    }
/// minus operator
    NozRGB& operator-=(float f)
    {
        r -= f;
        g -= f;
        b -= f;
        return *this;
    }
/// minus operator
    NozRGB operator-() const
    {
        NozRGB temp;
        temp.r = -r;
        temp.g = -g;
        temp.b = -b;
        return temp;
    }
/// multiply operator
    NozRGB operator*(const NozRGB& rgb) const
    {
        NozRGB temp;
        temp.r = r * rgb.r;
        temp.g = g * rgb.g;
        temp.b = b * rgb.b;
        return temp;
    }
/// multiply operator
    NozRGB operator*=(const NozRGB& rgb)
    {
        r *= rgb.r;
        g *= rgb.g;
        b *= rgb.b;
        return *this;
    }
/// multiply operator
    NozRGB operator*(float f) const
    {
        NozRGB temp;
        temp.r = r * f;
        temp.g = g * f;
        temp.b = b * f;
        return temp;
    }
/// multiply operator
    NozRGB operator*=(float f)
    {
        r *= f;
        g *= f;
        b *= f;
        return *this;
    }
/// divide operator
    NozRGB operator/(const NozRGB& rgb) const
    {
        NozRGB temp;
        temp.r = r / rgb.r;
        temp.g = g / rgb.g;
        temp.b = b / rgb.b;
        return temp;
    }
/// divide operator
    NozRGB operator/=(const NozRGB& rgb)
    {
        r /= rgb.r;
        g /= rgb.g;
        b /= rgb.b;
        return *this;
    }
/// divide operator
    NozRGB operator/(float f) const
    {
        NozRGB temp;
        //float inv = 1.0f / f;
        temp.r = r / f;
        temp.g = g / f;
        temp.b = b / f;
        return temp;
    }
/// divide operator
    NozRGB operator/=(float f)
    {
        //float inv = 1.0f / f;
        r /= f;
        g /= f;
        b /= f;
        return *this;
    }
/// comparaison operator
    bool operator==(const NozRGB& rgb) const
    {
        return (r == rgb.r && g == rgb.g && b == rgb.b);
    }
/// comparaison operator
    bool operator!=(const NozRGB& rgb) const
    {
        return !(*this == rgb);
    }
/// copy operator
    NozRGB& operator=(float f)
    {
        r = f;
        g = f;
        b = f;
        return *this;
    }
/// copy operator
    float& operator[](unsigned int i)
    {
        return *(&r + i); 
    }
/// copy operator
    const float& operator[](unsigned int i) const
    {
        return *(&r + i); 
    }

    friend NozRGB operator*(float f, const NozRGB& rgb);
    friend NozRGB operator+(float f, const NozRGB& rgb);
    friend NozRGB operator-(float f, const NozRGB& rgb);
};
/// multiply operator
inline NozRGB operator*(float f, const NozRGB& rgb)
{
    return rgb * f;
}
/// add operator
inline NozRGB operator+(float f, const NozRGB& rgb)
{
    return rgb + f;
}
/// minus operator
inline NozRGB operator-(float f, const NozRGB& rgb)
{
    NozRGB temp;
    temp.r = f - rgb.r;
    temp.g = f - rgb.g;
    temp.b = f - rgb.b;
    return temp;
}

/**
* RGB color + alpha
*/
struct NozRGBA
{
/// red	
    float r;
/// green	
	float g; 
/// blue	
	float b;
/// alpha	
	float a;
    NozRGBA()
    {
        r = 0.0; g = 0.0; b = 0.0; a = 1.0;
    }
/// 4 floats to RGBA
    NozRGBA(float r, float g, float b, float a){ 
        this->r = r; 
        this->g = g; 
        this->b = b; 
        this->a = a; 
    }
/// RGB + alpha float to RGBA
    NozRGBA(const NozRGB &col, const float &a)
    {
        this->r = col.r;
        this->g = col.g;
        this->b = col.b;
        this->a = a;
    }
/// return nozRGB
    NozRGB& rgb()
    {
        return *static_cast<NozRGB*>(static_cast<void*>(this));
    }
/// return nozRGB
    const NozRGB& rgb() const
    {
        return *static_cast<const NozRGB*>(static_cast<const void*>(this));
    }

/// add operator
    NozRGBA operator+(const NozRGBA& rgba) const
    {
        NozRGBA temp;
        temp.r = r + rgba.r;
        temp.g = g + rgba.g;
        temp.b = b + rgba.b;
        temp.a = a + rgba.a;
        return temp;
    }
/// add operator
    NozRGBA& operator+=(const NozRGBA& rgba)
    {
        r += rgba.r;
        g += rgba.g;
        b += rgba.b;
        a += rgba.a;
        return *this;
    }
/// add operator
    NozRGBA operator+(float f) const
    {
        NozRGBA temp;
        temp.r = r + f;
        temp.g = g + f;
        temp.b = b + f;
        temp.a = a + f;
        return temp;
    }
/// add operator
    NozRGBA& operator+=(float f)
    {
        r += f;
        g += f;
        b += f;
        a += f;
        return *this;
    }
/// minus operator
    NozRGBA operator-(const NozRGBA& rgba) const
    {
        NozRGBA temp;
        temp.r = r - rgba.r;
        temp.g = g - rgba.g;
        temp.b = b - rgba.b;
        temp.a = a - rgba.a;
        return temp;
    }
/// minus operator
    NozRGBA& operator-=(const NozRGBA& rgba)
    {
        r -= rgba.r;
        g -= rgba.g;
        b -= rgba.b;
        a -= rgba.a;
        return *this;
    }
/// minus operator
    NozRGBA operator-(float f) const
    {
        NozRGBA temp;
        temp.r = r - f;
        temp.g = g - f;
        temp.b = b - f;
        temp.a = a - f;
        return temp;
    }
/// minus operator
    NozRGBA& operator-=(float f)
    {
        r -= f;
        g -= f;
        b -= f;
        a -= f;
        return *this;
    }
/// minus operator
    NozRGBA operator-() const
    {
        NozRGBA temp;
        temp.r = -r;
        temp.g = -g;
        temp.b = -b;
        temp.a = -a;
        return temp;
    }
/// multiply operator
    NozRGBA operator*(const NozRGBA& rgba) const
    {
        NozRGBA temp;
        temp.r = r * rgba.r;
        temp.g = g * rgba.g;
        temp.b = b * rgba.b;
        temp.a = a * rgba.a;
        return temp;
    }
/// multiply operator
    NozRGBA operator*=(const NozRGBA& rgba)
    {
        r *= rgba.r;
        g *= rgba.g;
        b *= rgba.b;
        a *= rgba.a;
        return *this;
    }
/// multiply operator
    NozRGBA operator*(float f) const
    {
        NozRGBA temp;
        temp.r = r * f;
        temp.g = g * f;
        temp.b = b * f;
        temp.a = a * f;
        return temp;
    }
/// multiply operator
    NozRGBA operator*=(float f)
    {
        r *= f;
        g *= f;
        b *= f;
        a *= f;
        return *this;
    }
/// divide operator
    NozRGBA operator/(const NozRGBA& rgba) const
    {
        NozRGBA temp;
        temp.r = r / rgba.r;
        temp.g = g / rgba.g;
        temp.b = b / rgba.b;
        temp.a = a / rgba.a;
        return temp;
    }
/// divide operator
    NozRGBA operator/=(const NozRGBA& rgba)
    {
        r /= rgba.r;
        g /= rgba.g;
        b /= rgba.b;
        a /= rgba.a;
        return *this;
    }
/// divide operator
    NozRGBA operator/(float f) const
    {
        NozRGBA temp;

        temp.r = r /f ;
        temp.g = g /f;
        temp.b = b /f;
        temp.a = a /f;
        return temp;
    }
/// divide operator
    NozRGBA operator/=(float f)
    {
        r /= f;
        g /= f;
        b /= f;
        a /= f;
        return *this;
    }
/// comparaison operator
    bool operator==(const NozRGBA& rgba) const
    {
        return (r == rgba.r && g == rgba.g && b == rgba.b && a == rgba.a);
    }
/// comparaison operator
    bool operator!=(const NozRGBA& rgba) const
    {
        return !(*this == rgba);
    }
/// copy operator
    NozRGBA& operator=(float f)
    {
        r = f;
        g = f;
        b = f;
        a = f;
        return *this;
    }
/// copy operator
    float& operator[](unsigned int i)
    {
        return *(&r + i);  // warning: no bounds checking!
    }
/// copy operator
    const float& operator[](unsigned int i) const
    {
        return *(&r + i);  // warning: no bounds checking!
    }

    friend NozRGBA operator*(float f, const NozRGBA& rgba);
    friend NozRGBA operator+(float f, const NozRGBA& rgba);
    friend NozRGBA operator-(float f, const NozRGBA& rgba);
};
/// multiply operator
inline NozRGBA operator*(float f, const NozRGBA& rgba)
{
    return rgba * f;
}
/// add operator
inline NozRGBA operator+(float f, const NozRGBA& rgba)
{
    return rgba + f;
}
/// minus operator
inline NozRGBA operator-(float f, const NozRGBA& rgba)
{
    NozRGBA temp;
    temp.r = f - rgba.r;
    temp.g = f - rgba.g;
    temp.b = f - rgba.b;
    temp.a = f - rgba.a;
    return temp;
}



/** \name Color Operations
* \{
*/

/**
* Create a RGB color using the same value for all components
*/
inline NozRGB nozRGB(float f)
{
    return NozRGB(f,f,f);
}

/**
* Create a RGB color from its components
*/
inline NozRGB nozRGB(float r, float g, float b)
{
    return NozRGB(r,g,b);
}

/**
* Create a RGBA color from its components
*/
inline NozRGBA nozRGBA(const float r, float g, float b, float a)
{
    return NozRGBA(r, g, b, a );
}

/**
* Power of a RGB color by another color
*/
inline NozRGB NozRGBPow(const NozRGB& c, const NozRGB& pow)
{
    NozRGB out;
    out.r = powf(c.r, pow.r);
    out.g = powf(c.g, pow.g);
    out.b = powf(c.b, pow.b);
    return out;
}
/**
* Power of a RGB color by another color
*/
inline NozRGBA NozRGBAPow(const NozRGBA& c, const NozRGBA& pow)
{
    NozRGBA out;
    out.r = powf(c.r, pow.r);
    out.g = powf(c.g, pow.g);
    out.b = powf(c.b, pow.b);
    out.a = powf(c.a, pow.a);
    return out;
}


/**
* Clamp the RGB color vector to the specified range
*/
inline NozRGB NozRGBClamp(const NozRGB& c, float l, float h)
{
    NozRGB out;
    out.r = nozClamp(c.r, l, h);
    out.g = nozClamp(c.g, l, h);
    out.b = nozClamp(c.b, l, h);
    return out;
}

/**
* Clamp the RGBA color vector to the specified range
*/
inline NozRGBA NozRGBAClamp(const NozRGBA& c, float l, float h)
{
    NozRGBA out;
    out.r = nozClamp(c.r, l, h);
    out.g = nozClamp(c.g, l, h);
    out.b = nozClamp(c.b, l, h);
    out.a = nozClamp(c.a, l, h);
    return out;
}

/**
* Clip negative values
*/
inline void  NozColorClip(NozRGB& c)
{
    c.r = nozMax(0.0f, c.r);
    c.g = nozMax(0.0f, c.g);
    c.b = nozMax(0.0f, c.b);
}

/**
* Check for almost black
*/
inline bool nozColorIsSmall(const NozRGB& c, float epsilon = NOZ_EPSILON)
{
    return fabs(c.r) < epsilon && fabs(c.g) < epsilon && fabs(c.b) < epsilon;
}

/**
* Encode RGBA to int32
*/
inline unsigned int nozRGBATo_Int32(const NozRGBA &c)
{

    
    NozRGBA clampColor = NozRGBAClamp(c, 0, 1.0);
    int r_tmp = (int)(clampColor.r*255.0);
    int g_tmp = (int)(clampColor.g*255.0);
    int b_tmp = (int)(clampColor.b*255.0);
    int a_tmp = (int)(clampColor.a*255.0);

    return (r_tmp << 24) + (g_tmp << 16) + (b_tmp << 8) + (a_tmp);
    
}
/**
* Decode RGBA from int32
*/
inline NozRGBA nozRGBAFrom_Int32(unsigned int colorInt32)
{
    
    float r_tmp = (float)((colorInt32 >> 24) & 255)/255.0;
    float g_tmp = (float)((colorInt32 >> 16) & 255)/255.0;
    float b_tmp = (float)((colorInt32 >> 8) & 255)/255.0;
    float a_tmp = (float)(colorInt32 & 255)/255.0;
    return nozRGBA(r_tmp, g_tmp, b_tmp, a_tmp);
}

/**
* Convert a nozRGB to nozRGBA color 
*\remark setting alpha to 1.0
*/
inline NozRGBA NozRGBtoRGBA(const NozRGB& c)
{
    NozRGBA out;
    out.r = c.r;
    out.g = c.g;
    out.b = c.b;
    out.a = 1.f;
    return out;
}

/**
* Convert a nozRGBA to nozLAB color
*/

inline float _XYZf(float n) 
{
    if (n > 0.008856) {
        return pow(n, 1.0f / 3.0f);
        
    }
    else {
        return 7.787 * n + 16.0 / 116.0;
       
    }
    //return n > 0.008856 ? pow(n, 1.0 / 3.0) : (903.3 * n + 16.0) / 116.0;

}

/**
* Convert HSV to RGB
*/
inline NozRGB NozRGBfromHSV( float h, float s, float v)
{
    NozRGB out;
    double      p, q, t, ff;
    long        i;


    if (s <= 0) {
        out.r = out.g = out.b = v;
        return out;
    }


    if (h >= 360.0) h = 0.0;
    h /= 60.0;
    i = (long)h;
    ff = h - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch (i) {
    case 0:
        out.r = v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = v;
        break;
    case 5:
    default:
        out.r = v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

/**
* Convert camera id to color
*/
inline NozRGB colorFrom256_OtherCam(int id) {

    return NozRGBfromHSV(float(id), 1.0, 1.0);

}

/**
* Convert RGB to LAB
*/
inline NozLAB NozRGBtoLAB(const NozRGB& c)
{
    NozLAB out;
    float x, y, z;


    x = c.r * 0.41240000 + c.g * 0.35760000 + c.b * 0.18050000;
    y = c.r * 0.21260000 + c.g * 0.71520000 + c.b * 0.07220000;
    z = c.r * 0.01930000 + c.g * 0.11920000 + c.b * 0.95050000;


    x = x * 1.04257389 + y * 0.03089108 + z * -0.05281257;
    y = x * 0.02219345 + y * 1.00185663 + z * -0.02107375;
    z = x * -0.00116488 + y * -0.00342053 + z* 0.76178908;

    float x_xn = x / CIE_X;
    float y_yn = y / CIE_Y;
    float z_zn = z / CIE_Z;

    float f_x_xn = _XYZf(x_xn);
    float f_y_yn = _XYZf(y_yn);
    float f_z_zn = _XYZf(z_zn);

    out.l = nozMax(0.0, 116.0 * f_y_yn - 16.0);
    out.a = 500.0 * (f_x_xn - f_y_yn);
    out.b = 200.0 * (f_y_yn - f_z_zn);

    return out;

}

/**
* Convert RGBA to LAB
*/
inline NozLAB NozRGBtoLAB(const NozRGBA& c)
{
    NozLAB out;
    float x, y, z;


    x = c.r * 0.41240000 + c.g * 0.35760000 + c.b * 0.18050000;
    y = c.r * 0.21260000 + c.g * 0.71520000 + c.b * 0.07220000;
    z = c.r * 0.01930000 + c.g * 0.11920000 + c.b * 0.95050000;


    x = x * 1.04257389 + y * 0.03089108 + z * -0.05281257;
    y = x * 0.02219345 + y * 1.00185663 + z * -0.02107375;
    z = x * -0.00116488 + y * -0.00342053 + z* 0.76178908;

    float x_xn = x / CIE_X;
    float y_yn = y / CIE_Y;
    float z_zn = z / CIE_Z;

    float f_x_xn = _XYZf(x_xn);
    float f_y_yn = _XYZf(y_yn);
    float f_z_zn = _XYZf(z_zn);

    out.l = nozMax(0.0, 116.0 * f_y_yn - 16.0);
    out.a = 500.0 * (f_x_xn - f_y_yn);
    out.b = 200.0 * (f_y_yn - f_z_zn);

    return out;

}

/**
* Compute the difference between two NozLAB colors (non-linear)
*/
inline float NozDeltaLAB(NozLAB lab1, NozLAB lab2)
{
    NozLAB deltaLAB = lab1 - lab2;

    float c1 = sqrt(lab1.a * lab1.a + lab1.b * lab1.b);
    float c2 = sqrt(lab2.a * lab2.a + lab2.b * lab2.b);
    float deltaC = c1 - c2;

    float deltaH = deltaLAB.a * deltaLAB.a + deltaLAB.b * deltaLAB.b - deltaC * deltaC;
    deltaH = deltaH < 0 ? 0 : sqrt(deltaH);

    const float sl = 1.0;
    const float kc = 1.0;
    const float kh = 1.0;

    float sc = 1.0f + 0.45f * c1;
    float sh = 1.0f + 0.15f * c1;

    float deltaLKlsl = deltaLAB.l / (1.0f * sl);
    float deltaCkcsc = deltaC / (kc * sc);
    float deltaHkhsh = deltaH / (kh * sh);
    float i = deltaLKlsl * deltaLKlsl + deltaCkcsc * deltaCkcsc + deltaHkhsh * deltaHkhsh;
    return i < 0 ? 0 : sqrt(i);
}


/*\}*/

/** \name Constants
* \{
*/
/// Black RGB
#define NOZ_RGB_BLACK NozRGB(0.0f, 0.0f, 0.0f);
/// Red RGB
#define NOZ_RGB_RED NozRGB(1.0f, 0.0f, 0.0f);
/// Green RGB
#define NOZ_RGB_GREEN NozRGB(0.0f, 1.0f, 0.0f);
/// Blue RGB
#define NOZ_RGB_BLUE NozRGB(0.0f, 0.0f, 1.0f);
/// White RGB
#define NOZ_RGB_WHITE NozRGB(1.0f, 1.0f, 1.0f);
/// Black RGBA
#define NOZ_RGBA_BLACK NozRGBA(0.0f, 0.0f, 0.0f, 0.0f);
/// White RGBA
#define NOZ_RGBA_WHITE NozRGBA(1.0f, 1.0f, 1.0f, 1.0f);
/*\}*/

/*\}*/

#endif