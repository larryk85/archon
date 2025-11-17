![**ARCHON** Logo](./images/archon_full.png)

**ARCHON** is a high-performance virtual machine and hybrid instruction set architecture designed for ultra-low latency execution with strong hardware affinity. It blends a RISC-V foundation with carefully selected CISC-style extensions inspired by AMD64 and ARM64, creating a universal ISA that is both compact and expressive.

**ARCHON** aims to deliver near-native performance with predictable behavior, minimal overhead, and a deterministic execution model suitable for embedded systems, high-performance computing, and custom language runtimes.

## Features

- **Hybrid Universal ISA**
  - RISC-V base with practical, high-value extensions.
  - Common instruction patterns from x86-64 and AArch64 integrated.
  - Focused on hardware and static compilation affinity.

- **Low-Latency Execution**
  - Slim decoding pipeline.
  - Deterministic scheduling and predictable timing.
  - Optimized for JIT/AOT compilation and direct hardware mapping.

- **Hardware-Affine Design**
  - Explicit modeling of load/store, ALU, and fused operations.
  - Easy translation to GPU, DSP, or CPU backends.

- **Deterministic Semantics**
  - No undefined or implementation-dependent behavior.
  - Strong guarantees around memory and control flow.

- **Modular Runtime**
  - JIT/AOT acceleration by default.
  - A baseline interpreter for fallback on unsupported systems.
  - Designed to embed easily into other systems.

## Getting Started

**ARCHON** does not yet provide a stable public API, but the following components are available inside the repository:

- `archon-core`: Core ISA definition and instruction metadata.
- `archon-rt`: Runtime, interpreter, and execution engine.
- `archon-tools`: Assembly, disassembly, and inspection utilities.

To build the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Example

Below is a small example demonstrating how to assemble and execute a simple **ARCHON** program:

```
; add two registers and store result
add   r1, r2, r3
store r3, [r0 + 8]
halt
```

## Roadmap

- Formal ISA specification
- JIT/AOT backend for x86-64, ARM64, and RV64GC
- GPU-aware primitives and vector operations
- Deterministic concurrency model
- Verified reference interpreter
- Tooling: assembler, disassembler, debugger

## Contributing

Contributions are welcome. Please open an issue or submit a pull request with a clear description of the change.

## License

This project is released under the MIT license unless otherwise noted.
