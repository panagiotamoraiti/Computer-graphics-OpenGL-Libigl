# Install script for directory: C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/out/install/x64-Debug (default)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Cholesky"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/CholmodSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Core"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Dense"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Eigen"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Eigenvalues"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Geometry"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Householder"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/IterativeLinearSolvers"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Jacobi"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/LU"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/MetisSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/OrderingMethods"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/PaStiXSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/PardisoSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/QR"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/QtAlignedMalloc"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SPQRSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SVD"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/Sparse"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SparseCholesky"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SparseCore"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SparseLU"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SparseQR"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/StdDeque"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/StdList"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/StdVector"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/SuperLUSupport"
    "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "C:/Users/zoes_/OneDrive/Υπολογιστής/IglTesting/eigen/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

