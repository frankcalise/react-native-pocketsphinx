#!/bin/bash

CPP_DIRS=(

  "android/src/main/cpp"
  "cpp"
)

if which clang-format >/dev/null; then
  DIRS=$(printf "%s " "${CPP_DIRS[@]}")
  find $DIRS -type f \( -name "*.h" -o -name "*.hpp" -o -name "*.cpp" -o -name "*.m" -o -name "*.mm" -o -name "*.c" \) -print0 | while read -d $'\0' file; do
    clang-format -style=file:./.clang-format -i "$file"
  done
else
  echo "error: clang-format not installed, install with 'brew install clang-format' (or manually from https://clang.llvm.org/docs/ClangFormat.html)"
  exit 1
fi