#
# Copyright 2024 Adobe. All rights reserved.
# This file is licensed to you under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License. You may obtain a copy
# of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
# OF ANY KIND, either express or implied. See the License for the specific language
# governing permissions and limitations under the License.
#
if(TARGET polyscope::polyscope)
    return()
endif()

message(STATUS "Third-party (external): creating target 'polyscope::polyscope'")

if(NOT TARGET stb)
    include(stb)
    add_library(stb INTERFACE)
    target_link_libraries(stb INTERFACE stb::image stb::image_write)
endif()
include(glfw)
include(imgui)
include(nlohmann_json)
include(glad)

include(CPM)
CPMAddPackage(
    NAME polyscope
    GITHUB_REPOSITORY nmwsharp/polyscope
    GIT_TAG bb034326842313151c9419e51fac20c6c4ef8a93
)

add_library(polyscope::polyscope ALIAS polyscope)
