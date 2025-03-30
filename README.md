# Simple INI Parser Fuzzer

An INI parser with fuzzing support using libFuzzer.

## Project Structure

- `src/` - Source code for the INI parser and fuzzing target
- `test/corpus/` - Initial corpus files for fuzzing
- `CMakeLists.txt` - Build configuration

## Building Locally

To build the project locally, you need:
- CMake 3.10+
- Clang/LLVM with fuzzing support

```bash
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
make
```

## Running the Fuzzer

To run the fuzzer with the initial corpus:

```bash
./build/fuzzing test/corpus/
```
