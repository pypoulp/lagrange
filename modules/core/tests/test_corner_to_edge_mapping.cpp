/*
 * Copyright 2020 Adobe. All rights reserved.
 * This file is licensed to you under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
 * OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */
#include <lagrange/Mesh.h>
#include <lagrange/corner_to_edge_mapping.h>
#include <lagrange/io/load_mesh.h>

#include <lagrange/testing/common.h>

namespace {

template <typename DerivedW>
bool readDMAT(const std::string filename, Eigen::PlainObjectBase<DerivedW>& W)
{
    std::ifstream in(filename);
    if (!in) {
        lagrange::logger().error("Could not open file: {}", filename);
        return false;
    }

    int num_rows, num_cols;
    if (!(in >> num_cols >> num_rows)) {
        lagrange::logger().error("Could not read file header");
        return false;
    }
    la_runtime_assert(num_rows >= 0);
    la_runtime_assert(num_cols >= 0);

    // Resize output to fit matrix, only if non-empty since this will trigger an
    // error on fixed size matrices before reaching binary data.
    bool empty = num_rows == 0 || num_cols == 0;
    if (!empty) {
        W.resize(num_rows, num_cols);
    }

    // Loop over columns slowly
    for (int j = 0; j < num_cols; j++) {
        // loop over rows (down columns) quickly
        for (int i = 0; i < num_rows; i++) {
            if (!(in >> W(i, j))) {
                lagrange::logger().error("Could not read matrix entry ({}, {})", i, j);
                return false;
            }
        }
    }

    return true;
}

} // namespace

TEST_CASE("corner_to_edge_mapping: replicability", "[core]")
{
    auto mesh = lagrange::testing::load_mesh<lagrange::TriangleMesh3D>("open/core/hemisphere.obj");
    REQUIRE(mesh);
    REQUIRE(mesh->get_num_vertices() == 341);
    REQUIRE(mesh->get_num_facets() == 640);
    Eigen::VectorXi c2e_0, c2e_1;
    auto ne0 = lagrange::corner_to_edge_mapping(mesh->get_facets(), c2e_0);
    auto ne1 = lagrange::corner_to_edge_mapping(mesh->get_facets(), c2e_1);
    REQUIRE(ne0 == ne1);
    REQUIRE(ne0 == c2e_0.maxCoeff() + 1);
    REQUIRE(c2e_0.size() == mesh->get_facets().size());
    REQUIRE(c2e_0.size() == c2e_1.size());
    REQUIRE(c2e_0 == c2e_1);
}

TEST_CASE("corner_to_edge_mapping: regression", "[core]")
{
    auto mesh = lagrange::testing::load_mesh<lagrange::TriangleMesh3D>("open/core/hemisphere.obj");
    REQUIRE(mesh);
    REQUIRE(mesh->get_num_vertices() == 341);
    REQUIRE(mesh->get_num_facets() == 640);
    Eigen::VectorXi c2e, c2e_ref;
    auto ne = lagrange::corner_to_edge_mapping(mesh->get_facets(), c2e);
    REQUIRE(ne == c2e.maxCoeff() + 1);
    REQUIRE(c2e.size() == mesh->get_facets().size());
    auto ret = ::readDMAT(
        lagrange::testing::get_data_path("open/core/hemisphere.edges.dmat").string(),
        c2e_ref);
    REQUIRE(ret);
    REQUIRE(c2e.size() == c2e_ref.size());
    REQUIRE(c2e == c2e_ref);
}
