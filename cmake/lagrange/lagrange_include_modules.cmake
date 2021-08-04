#
# Copyright 2020 Adobe. All rights reserved.
# This file is licensed to you under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License. You may obtain a copy
# of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
# OF ANY KIND, either express or implied. See the License for the specific language
# governing permissions and limitations under the License.
#
function(lagrange_include_modules)
    foreach(name IN ITEMS ${ARGN})
        if(NOT TARGET lagrange::${name})
            add_subdirectory(${PROJECT_SOURCE_DIR}/modules/${name} ${PROJECT_BINARY_DIR}/modules/lagrange_${name})
        endif()

        if(NOT TARGET lagrange::${name})
            message(FATAL_ERROR "Failed to create lagrange module: ${name}")
        endif()

        if(TARGET lagrange_${name}_)
            set_target_properties(lagrange_${name}_ PROPERTIES FOLDER "Lagrange")
        elseif(TARGET lagrange_${name})
            set_target_properties(lagrange_${name} PROPERTIES FOLDER "Lagrange")
        endif()
    endforeach()
endfunction()
