/*
 * Copyright 2023 Adobe. All rights reserved.
 * This file is licensed to you under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
 * OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */
#include <lagrange/SurfaceMeshTypes.h>
#include <lagrange/attribute_names.h>
#include <lagrange/compute_normal.h>
#include <lagrange/testing/api.h>
#include <lagrange/testing/create_test_mesh.h>

namespace lagrange::testing {

template <typename Scalar, typename Index>
SurfaceMesh<Scalar, Index> create_test_cube(CreateOptions options)
{
    SurfaceMesh<Scalar, Index> cube;
    cube.add_vertex({-1, -1, -1});
    cube.add_vertex({1, -1, -1});
    cube.add_vertex({1, 1, -1});
    cube.add_vertex({-1, 1, -1});
    cube.add_vertex({-1, -1, 1});
    cube.add_vertex({1, -1, 1});
    cube.add_vertex({1, 1, 1});
    cube.add_vertex({-1, 1, 1});

    cube.add_triangle(0, 2, 1);
    cube.add_triangle(0, 3, 2);
    cube.add_triangle(4, 5, 6);
    cube.add_triangle(4, 6, 7);
    cube.add_triangle(1, 2, 6);
    cube.add_triangle(1, 6, 5);
    cube.add_triangle(3, 0, 7);
    cube.add_triangle(7, 0, 4);
    cube.add_triangle(2, 3, 7);
    cube.add_triangle(2, 7, 6);
    cube.add_triangle(0, 1, 4);
    cube.add_triangle(4, 1, 5);

    if (options.with_indexed_uv) {
        std::array<Scalar, 28> uv_values{0.25f, 0.0f, 0.5f,  0.0f,  0.0f,  0.25f, 0.25f,
                                         0.25f, 0.5f, 0.25f, 0.75f, 0.25f, 0.0f,  0.5f,
                                         0.25f, 0.5f, 0.5f,  0.5f,  0.75f, 0.5f,  0.25f,
                                         0.75f, 0.5f, 0.75f, 0.25f, 1.0f,  0.5f,  1.0f};
        std::array<Index, 36> uv_indices{10, 13, 11, 10, 12, 13, 7,  8,  4, 7, 4,  3,
                                         9,  5,  4,  9,  4,  8,  2,  6,  3, 3, 6,  7,
                                         1,  0,  3,  1,  3,  4,  10, 11, 7, 7, 11, 8};
        cube.template create_attribute<Scalar>(
            AttributeName::texcoord,
            AttributeElement::Indexed,
            AttributeUsage::UV,
            2,
            uv_values,
            uv_indices);
    }

    if (options.with_indexed_normal) {
        compute_normal<Scalar, Index>(cube, static_cast<Scalar>(M_PI / 4));
    }

    return cube;
}

template <typename Scalar, typename Index>
SurfaceMesh<Scalar, Index> create_test_sphere(CreateOptions options)
{
    SurfaceMesh<Scalar, Index> sphere;
    sphere.add_vertices(
        42,
        {0.f,        -1.f,       0.f,        0.723607f,  -0.44722f,  0.525725f,  -0.276388f,
         -0.44722f,  0.850649f,  -0.894426f, -0.447216f, 0.f,        -0.276388f, -0.44722f,
         -0.850649f, 0.723607f,  -0.44722f,  -0.525725f, 0.276388f,  0.44722f,   0.850649f,
         -0.723607f, 0.44722f,   0.525725f,  -0.723607f, 0.44722f,   -0.525725f, 0.276388f,
         0.44722f,   -0.850649f, 0.894426f,  0.447216f,  0.f,        0.f,        1.f,
         0.f,        -0.162456f, -0.850654f, 0.499995f,  0.425323f,  -0.850654f, 0.309011f,
         0.262869f,  -0.525738f, 0.809012f,  0.850648f,  -0.525736f, 0.f,        0.425323f,
         -0.850654f, -0.309011f, -0.52573f,  -0.850652f, 0.f,        -0.688189f, -0.525736f,
         0.499997f,  -0.162456f, -0.850654f, -0.499995f, -0.688189f, -0.525736f, -0.499997f,
         0.262869f,  -0.525738f, -0.809012f, 0.951058f,  0.f,        0.309013f,  0.951058f,
         0.f,        -0.309013f, 0.f,        0.f,        1.f,        0.587786f,  0.f,
         0.809017f,  -0.951058f, 0.f,        0.309013f,  -0.587786f, 0.f,        0.809017f,
         -0.587786f, 0.f,        -0.809017f, -0.951058f, 0.f,        -0.309013f, 0.587786f,
         0.f,        -0.809017f, 0.f,        0.f,        -1.f,       0.688189f,  0.525736f,
         0.499997f,  -0.262869f, 0.525738f,  0.809012f,  -0.850648f, 0.525736f,  0.f,
         -0.262869f, 0.525738f,  -0.809012f, 0.688189f,  0.525736f,  -0.499997f, 0.162456f,
         0.850654f,  0.499995f,  0.52573f,   0.850652f,  0.f,        -0.425323f, 0.850654f,
         0.309011f,  -0.425323f, 0.850654f,  -0.309011f, 0.162456f,  0.850654f,  -0.499995f});

    sphere.add_triangles(
        80,
        {0,  13, 12, 1,  13, 15, 0,  12, 17, 0,  17, 19, 0,  19, 16, 1,  15, 22, 2,  14, 24, 3,
         18, 26, 4,  20, 28, 5,  21, 30, 1,  22, 25, 2,  24, 27, 3,  26, 29, 4,  28, 31, 5,  30,
         23, 6,  32, 37, 7,  33, 39, 8,  34, 40, 9,  35, 41, 10, 36, 38, 38, 41, 11, 38, 36, 41,
         36, 9,  41, 41, 40, 11, 41, 35, 40, 35, 8,  40, 40, 39, 11, 40, 34, 39, 34, 7,  39, 39,
         37, 11, 39, 33, 37, 33, 6,  37, 37, 38, 11, 37, 32, 38, 32, 10, 38, 23, 36, 10, 23, 30,
         36, 30, 9,  36, 31, 35, 9,  31, 28, 35, 28, 8,  35, 29, 34, 8,  29, 26, 34, 26, 7,  34,
         27, 33, 7,  27, 24, 33, 24, 6,  33, 25, 32, 6,  25, 22, 32, 22, 10, 32, 30, 31, 9,  30,
         21, 31, 21, 4,  31, 28, 29, 8,  28, 20, 29, 20, 3,  29, 26, 27, 7,  26, 18, 27, 18, 2,
         27, 24, 25, 6,  24, 14, 25, 14, 1,  25, 22, 23, 10, 22, 15, 23, 15, 5,  23, 16, 21, 5,
         16, 19, 21, 19, 4,  21, 19, 20, 4,  19, 17, 20, 17, 3,  20, 17, 18, 3,  17, 12, 18, 12,
         2,  18, 15, 16, 5,  15, 13, 16, 13, 0,  16, 12, 14, 2,  12, 13, 14, 13, 1,  14});

    if (options.with_indexed_uv) {
        std::array<Scalar, 126> uv_values{
            0.181819f, 0.f,       0.227273f, 0.078731f, 0.136365f, 0.078731f, 0.272728f, 0.157461f,
            0.318182f, 0.078731f, 0.363637f, 0.157461f, 0.909091f, 0.f,       0.954545f, 0.078731f,
            0.863636f, 0.078731f, 0.727273f, 0.f,       0.772727f, 0.078731f, 0.681818f, 0.078731f,
            0.545455f, 0.f,       0.590909f, 0.078731f, 0.5f,      0.078731f, 0.318182f, 0.236191f,
            0.09091f,  0.157461f, 0.181819f, 0.157461f, 0.136365f, 0.236191f, 0.818182f, 0.157461f,
            0.909091f, 0.157461f, 0.863636f, 0.236191f, 0.636364f, 0.157461f, 0.727273f, 0.157461f,
            0.681818f, 0.236191f, 0.454546f, 0.157461f, 0.545455f, 0.157461f, 0.5f,      0.236191f,
            0.227273f, 0.236191f, 0.045455f, 0.236191f, 0.772727f, 0.236191f, 0.590909f, 0.236191f,
            0.409092f, 0.236191f, 0.181819f, 0.314921f, 0.272728f, 0.314921f, 0.227273f, 0.393651f,
            0.f,       0.314921f, 0.09091f,  0.314921f, 0.045455f, 0.393651f, 0.727273f, 0.314921f,
            0.818182f, 0.314921f, 0.772727f, 0.393651f, 0.545455f, 0.314921f, 0.636364f, 0.314921f,
            0.590909f, 0.393651f, 0.363637f, 0.314921f, 0.454546f, 0.314921f, 0.409092f, 0.393651f,
            0.5f,      0.393651f, 0.454546f, 0.472382f, 0.681818f, 0.393651f, 0.636364f, 0.472382f,
            0.863636f, 0.393651f, 0.818182f, 0.472382f, 0.909091f, 0.314921f, 0.136365f, 0.393651f,
            0.09091f,  0.472382f, 0.318182f, 0.393651f, 0.272728f, 0.472382f, 0.954545f, 0.236191f,
            1.f,       0.157461f, 0.409092f, 0.078731f, 0.363637f, 0.f};
        std::array<Index, 240> uv_indices{
            0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 3,  5,  15, 16, 17, 18, 19,
            20, 21, 22, 23, 24, 25, 26, 27, 3,  15, 28, 16, 18, 29, 19, 21, 30, 22, 24, 31, 25, 27,
            32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 47, 48, 49, 47, 46, 48,
            46, 42, 48, 44, 50, 51, 44, 43, 50, 43, 39, 50, 41, 52, 53, 41, 40, 52, 40, 54, 52, 38,
            55, 56, 38, 37, 55, 37, 33, 55, 35, 57, 58, 35, 34, 57, 34, 45, 57, 32, 46, 45, 32, 27,
            46, 27, 42, 46, 31, 43, 42, 31, 24, 43, 24, 39, 43, 30, 40, 39, 30, 21, 40, 21, 54, 40,
            29, 37, 36, 29, 18, 37, 18, 33, 37, 28, 34, 33, 28, 15, 34, 15, 45, 34, 27, 31, 42, 27,
            26, 31, 26, 22, 31, 24, 30, 39, 24, 23, 30, 23, 19, 30, 21, 59, 54, 21, 20, 59, 20, 60,
            59, 18, 28, 33, 18, 17, 28, 17, 3,  28, 15, 32, 45, 15, 5,  32, 5,  25, 32, 14, 26, 25,
            14, 13, 26, 13, 22, 26, 11, 23, 22, 11, 10, 23, 10, 19, 23, 8,  20, 19, 8,  7,  20, 7,
            60, 20, 5,  61, 25, 5,  4,  61, 4,  62, 61, 2,  17, 16, 2,  1,  17, 1,  3,  17};
        sphere.template create_attribute<Scalar>(
            AttributeName::texcoord,
            AttributeElement::Indexed,
            AttributeUsage::UV,
            2,
            span<Scalar>(uv_values),
            span<Index>(uv_indices));
    }

    if (options.with_indexed_normal) {
        std::array<Scalar, 240> normal_values{
            0.1024f,  -0.9435f, 0.3151f,  0.7002f,  -0.6617f, 0.268f,   -0.268f,  -0.9435f,
            0.1947f,  -0.268f,  -0.9435f, -0.1947f, 0.1024f,  -0.9435f, -0.3151f, 0.905f,
            -0.3304f, 0.268f,   0.0247f,  -0.3304f, 0.9435f,  -0.8897f, -0.3304f, 0.3151f,
            -0.5746f, -0.3304f, -0.7488f, 0.5346f,  -0.3304f, -0.7779f, 0.8026f,  -0.1256f,
            0.5831f,  -0.3066f, -0.1256f, 0.9435f,  -0.9921f, -0.1256f, 0.f,      -0.3066f,
            -0.1256f, -0.9435f, 0.8026f,  -0.1256f, -0.5831f, 0.4089f,  0.6617f,  0.6284f,
            -0.4713f, 0.6617f,  0.5831f,  -0.7002f, 0.6617f,  -0.268f,  0.0385f,  0.6617f,
            -0.7488f, 0.724f,   0.6617f,  -0.1947f, 0.268f,   0.9435f,  -0.1947f, 0.4911f,
            0.7947f,  -0.3568f, 0.4089f,  0.6617f,  -0.6284f, -0.1024f, 0.9435f,  -0.3151f,
            -0.1876f, 0.7947f,  -0.5773f, -0.4713f, 0.6617f,  -0.5831f, -0.3313f, 0.9435f,
            0.f,      -0.6071f, 0.7947f,  0.f,      -0.7002f, 0.6617f,  0.268f,   -0.1024f,
            0.9435f,  0.3151f,  -0.1876f, 0.7947f,  0.5773f,  0.0385f,  0.6617f,  0.7488f,
            0.268f,   0.9435f,  0.1947f,  0.4911f,  0.7947f,  0.3568f,  0.724f,   0.6617f,
            0.1947f,  0.8897f,  0.3304f,  -0.3151f, 0.7947f,  0.1876f,  -0.5773f, 0.5746f,
            0.3304f,  -0.7488f, -0.0247f, 0.3304f,  -0.9435f, -0.3035f, 0.1876f,  -0.9342f,
            -0.5346f, 0.3304f,  -0.7779f, -0.905f,  0.3304f,  -0.268f,  -0.9822f, 0.1876f,
            0.f,      -0.905f,  0.3304f,  0.268f,   -0.5346f, 0.3304f,  0.7779f,  -0.3035f,
            0.1876f,  0.9342f,  -0.0247f, 0.3304f,  0.9435f,  0.5746f,  0.3304f,  0.7488f,
            0.7947f,  0.1876f,  0.5773f,  0.8897f,  0.3304f,  0.3151f,  0.3066f,  0.1256f,
            -0.9435f, 0.3035f,  -0.1876f, -0.9342f, 0.0247f,  -0.3304f, -0.9435f, -0.8026f,
            0.1256f,  -0.5831f, -0.7947f, -0.1876f, -0.5773f, -0.8897f, -0.3304f, -0.3151f,
            -0.8026f, 0.1256f,  0.5831f,  -0.7947f, -0.1876f, 0.5773f,  -0.5746f, -0.3304f,
            0.7488f,  0.3066f,  0.1256f,  0.9435f,  0.3035f,  -0.1876f, 0.9342f,  0.5346f,
            -0.3304f, 0.7779f,  0.9921f,  0.1256f,  0.f,      0.9822f,  -0.1876f, 0.f,
            0.905f,   -0.3304f, -0.268f,  0.4713f,  -0.6617f, -0.5831f, 0.1876f,  -0.7947f,
            -0.5773f, -0.0385f, -0.6617f, -0.7488f, -0.4089f, -0.6617f, -0.6284f, -0.4911f,
            -0.7947f, -0.3568f, -0.724f,  -0.6617f, -0.1947f, -0.724f,  -0.6617f, 0.1947f,
            -0.4911f, -0.7947f, 0.3568f,  -0.4089f, -0.6617f, 0.6284f,  0.7002f,  -0.6617f,
            -0.268f,  0.6071f,  -0.7947f, 0.f,      0.3313f,  -0.9435f, 0.f,      -0.0385f,
            -0.6617f, 0.7488f,  0.1876f,  -0.7947f, 0.5773f,  0.4713f,  -0.6617f, 0.5831f};
        std::array<Index, 240> normal_indices{
            0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,  6,  6,  6,  7,
            7,  7,  8,  8,  8,  9,  9,  9,  10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14,
            14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21,
            22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29,
            29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36,
            36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43,
            44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51,
            51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58,
            58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 65,
            66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 71, 72, 72, 72, 73,
            73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 78, 78, 78, 79, 79, 79};
        sphere.template create_attribute<Scalar>(
            AttributeName::normal,
            AttributeElement::Indexed,
            AttributeUsage::Normal,
            3,
            span<Scalar>(normal_values),
            span<Index>(normal_indices));
    }

    return sphere;
}

#define LA_X_create_test_mesh(_, Scalar, Index)                                         \
    template LA_TESTING_API SurfaceMesh<Scalar, Index> create_test_cube(CreateOptions); \
    template LA_TESTING_API SurfaceMesh<Scalar, Index> create_test_sphere(CreateOptions);
LA_SURFACE_MESH_X(create_test_mesh, 0)

} // namespace lagrange::testing
