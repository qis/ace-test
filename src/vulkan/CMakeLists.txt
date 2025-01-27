project(ace-vulkan LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

# =============================================================================
# spirv-headers
# =============================================================================
find_path(SPIRV_HEADERS_INCLUDE_DIRS "spirv/1.0/GLSL.std.450.h" REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${SPIRV_HEADERS_INCLUDE_DIRS})

# =============================================================================
# spirv-tools
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(SPIRV-Tools CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-static)
#
# find_package(SPIRV-Tools-link CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-link)
#
# find_package(SPIRV-Tools-lint CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-lint)
#
# find_package(SPIRV-Tools-opt CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-opt)

# The following targets are broken and need to be fixed.
#
# find_package(SPIRV-Tools-reduce CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-reduce)
#
# Tries to include:
# share/spirv-tools-reduce/SPIRV-Tools-reduceTargets.cmake instead of:
# share/spirv-tools-reduce/SPIRV-Tools-reduceTarget.cmake

find_program(SPIRV_AS spirv-as REQUIRED)
find_program(SPIRV_CFG spirv-cfg REQUIRED)
find_program(SPIRV_DIS spirv-dis REQUIRED)
find_program(SPIRV_LINK spirv-link REQUIRED)
find_program(SPIRV_LINT spirv-lint REQUIRED)
find_program(SPIRV_OPT spirv-opt REQUIRED)
find_program(SPIRV_REDUCE spirv-reduce REQUIRED)
find_program(SPIRV_VAL spirv-val REQUIRED)

# =============================================================================
# glslang
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(glslang CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#   glslang::glslang
#   glslang::glslang-default-resource-limits
#   glslang::SPIRV
#   glslang::SPVRemapper)

find_program(GLSLANG glslang REQUIRED)
find_program(SPIRV_REMAP spirv-remap REQUIRED)

# =============================================================================
# shaderc
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(unofficial-shaderc CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::shaderc::shaderc)

find_program(GLSLC glslc REQUIRED)

# =============================================================================
# vulkan-headers
# =============================================================================
find_package(VulkanHeaders CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Headers)

# =============================================================================
# vulkan-utility-libraries
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(VulkanUtilityLibraries CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#   Vulkan::SafeStruct
#   Vulkan::LayerSettings
#   Vulkan::UtilityHeaders
#   Vulkan::CompilerConfiguration)

# =============================================================================
# vulkan-memory-allocator
# =============================================================================
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GPUOpen::VulkanMemoryAllocator)

# =============================================================================
# volk
# =============================================================================
find_package(volk CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE volk::volk)
#target_link_libraries(${PROJECT_NAME} PRIVATE volk::volk_headers)

# =============================================================================
# convectionkernels
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(unofficial-convectionkernels CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#   unofficial::convectionkernels::convectionkernels)

# =============================================================================
# meshoptimizer
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(meshoptimizer CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE meshoptimizer::meshoptimizer)

find_program(GLTFPACK gltfpack REQUIRED)

# =============================================================================
# recastnavigation
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(recastnavigation CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#   RecastNavigation::Detour
#   RecastNavigation::Recast
#   RecastNavigation::DebugUtils
#   RecastNavigation::DetourCrowd)

# =============================================================================
# openfbx
# =============================================================================
# The following targets work, but are not directly required for now.
#
# find_package(unofficial-openfbx CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE unoffical::openfbx::openfbx)

# =============================================================================
# draco
# =============================================================================
find_package(draco CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE draco::draco)

# =============================================================================
# fastgltf
# =============================================================================
find_package(fastgltf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fastgltf::fastgltf)

# =============================================================================
# ktx
# =============================================================================
find_package(Ktx CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE KTX::ktx)
# target_link_libraries(${PROJECT_NAME} PRIVATE KTX::astcenc-avx2-static)
