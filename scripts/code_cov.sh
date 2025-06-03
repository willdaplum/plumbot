rm -rf build coverage coverage-html
CC=/opt/homebrew/opt/llvm/bin/clang CXX=/opt/homebrew/opt/llvm/bin/clang++ cmake -S all -B build -DENABLE_TEST_COVERAGE=1
cmake --build build 
cd build
LLVM_PROFILE_FILE=PlumbotTests.profraw ctest --output-on-failure
/opt/homebrew/opt/llvm/bin/llvm-profdata merge -sparse ./test/PlumbotTests.profraw -o plumbot.profdata
/opt/homebrew/opt/llvm/bin/llvm-cov show ./test/PlumbotTests \
  -instr-profile=plumbot.profdata \
  -format=html \
  -output-dir=coverage-html \
  -use-color

