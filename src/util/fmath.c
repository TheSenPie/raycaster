#include "fmath.h"
#include "../util/util.h"

int ivec3scmp(ivec3s a, ivec3s b) {
    return memcmp(&a, &b, sizeof(ivec3s));
}

s64 ivec3shash(ivec3s v) {
    s64 h = 0;
    for(int i = 0; i < 3; i++) {
        h ^= v.raw[i] + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
}


bool ray_triangle_intersect( 
    vec3s orig, vec3s dir, 
    vec3s v0, vec3s v1, vec3s v2, 
    float *t, float *u, float *v) 
{
    vec3s v0v1, v0v2, pvec, tvec, qvec;
    float det, invDet;
    v0v1 = glms_vec3_sub(v1, v0); 
    v0v2 = glms_vec3_sub(v2, v0); 
    pvec = glms_cross(dir, v0v2);
    det = glms_dot(v0v1, pvec); 

    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < F32_EPSILON) return false;  

    invDet = 1.0f / det; 
 
    tvec = glms_vec3_sub(orig, v0); 
    *u = glms_vec3_dot(tvec, pvec) * invDet; 
    if (*u < 0 || *u > 1) return false; 
 
    qvec = glms_vec3_cross(tvec, v0v1);
    *v = glms_vec3_dot(dir, qvec) * invDet; 
    if (*v < 0 || *u + *v > 1) return false; 
 
    *t = glms_vec3_dot(v0v2, qvec) * invDet; 
 
    return true;
}