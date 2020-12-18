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
#include <iostream>

#include <lagrange/common.h>
#include <lagrange/create_mesh.h>
#include <lagrange/io/load_mesh.h>
#include <lagrange/io/save_mesh.h>
#include <lagrange/mesh_cleanup/remove_degenerate_triangles.h>

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_mesh output_mesh" << std::endl;
        return 1;
    }

    auto mesh = lagrange::io::load_mesh<lagrange::TriangleMesh3D>(argv[1]);
    mesh = lagrange::remove_degenerate_triangles(*mesh);
    lagrange::io::save_mesh(argv[2], *mesh);

    return 0;
}
