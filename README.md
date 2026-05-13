[![CI](https://github.com/shirmanovak410-ops/lab06/actions/workflows/ci.yml/badge.svg)](https://github.com/shirmanovak410-ops/lab05/actions/workflows/ci.yml)
# Lab06
## Отчёт к lab06
В рамках выполнения данной лабораторной работы мною были выполнены команды из tutorial с некоторыми изменениями:
1) Скопирован репозиторий из lab05.
2) Изменён CMakeLists.txt:
```bash
$ git diff
diff --git a/CMakeLists.txt b/CMakeLists.txt
index 605c0e8..3d7e62f 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -6,6 +6,13 @@ set(CMAKE_CXX_STANDARD_REQUIRED ON)
 option(BUILD_EXAMPLES "Build examples" OFF)

 project(print)
+set(PRINT_VERSION_MAJOR 0)
+set(PRINT_VERSION_MINOR 1)
+set(PRINT_VERSION_PATCH 0)
+set(PRINT_VERSION_TWEAK 0)
+set(PRINT_VERSION
+  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
+set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

 add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

```
3) Добавлены файлы DESCRIPTION и ChangeLog.md
```bash
$ cat DESCRIPTION
Print library is a static C++ library for printing strings to console.
It provides simple and efficient way to output text with version control.
EOF

$ cat ChangeLog.md
 * ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
- Added versioning support
- Created CPack configuration
```
4) Написан конфигурационный файл для CPack CPackConfig.cmake:
```cmake
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

include(CPack)
```
5) Запушены все изменения и тег:
```bash
$ git push origin main --tags
Username for 'https://github.com': shirmanovak410-ops
Password for 'https://shirmanovak410-ops@github.com':
Перечисление объектов: 138, готово.
Подсчет объектов: 100% (138/138), готово.
При сжатии изменений используется до 8 потоков
Сжатие объектов: 100% (83/83), готово.
Запись объектов: 100% (138/138), 31.45 КиБ | 1.96 МиБ/с, готово.
Total 138 (delta 46), reused 96 (delta 31), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (46/46), done.
To https://github.com/shirmanovak410-ops/lab06
 * [new branch]      main -> main
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```

6) Произведена ручная сборка (2мя способами)

Первый способ:
```bash
$ cmake -S . -B _build
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ksu/shirmanovak410-ops/workspace/projects/lab06/_build
$ cmake --build _build
[ 50%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[100%] Linking CXX static library libprint.a
[100%] Built target print
ksu@skalab3:~/shirmanovak410-ops/workspace/projects/lab06$ cd _build
ksu@skalab3:~/shirmanovak410-ops/workspace/projects/lab06/_build$ cpack -G "TGZ"
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print []
CPack: Create package
CPack: - package: /home/ksu/shirmanovak410-ops/workspace/projects/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
$ ls -la *.tar.gz
-rw-rw-r-- 1 ksu ksu 2882 мая 13 12:48 print-0.1.0.0-Linux.tar.gz
$ tar -tzf *.tar.gz | head -20
print-0.1.0.0-Linux/include/
print-0.1.0.0-Linux/include/print.hpp
print-0.1.0.0-Linux/cmake/
print-0.1.0.0-Linux/cmake/print-config-noconfig.cmake
print-0.1.0.0-Linux/cmake/print-config.cmake
print-0.1.0.0-Linux/lib/
print-0.1.0.0-Linux/lib/libprint.a
$ cd ..
```
Второй способ:
```bash
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/danila/Wartheree/workspace/projects/lab06/_build

$ cmake --build _build --target package
[100%] Built target print
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print []
CPack: Create package
CPack: - package: /home/ksu/shirmanovak410-ops/workspace/projects/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
```
В результате выполнения обоих способов сборки сгенерирован архив print-0.1.0.0-Linux.tar.gz

7) Этот архив помещен в локальную директорию artifacts:
```bash
$ mkdir artifacts
$ mv _build/*.tar.gz artifacts
$ tree artifacts
artifacts
└── print-0.1.0.0-Linux.tar.gz

1 directory, 1 file
```
