# 🖥️ Vole Machine Simulator

Welcome to the **Vole Machine Simulator**! This project provides a graphical interface for simulating a virtual machine’s CPU, memory, registers, and control unit. The Vole Machine simulator is designed to help users understand low-level programming and computer architecture concepts by visualizing data processing and control flow.

## ✨ Features

- **Memory and Register Management**: View, modify, and clear memory and register contents.
- **Instruction Execution**: Load, store, and execute instructions with options for step-by-step or continuous run.
- **Output Screen**: Displays results of executed instructions, including ASCII, hexadecimal, integer, and floating-point values.
- **Program Control**: Set the starting address, fetch instructions, and manage the program counter.
- **File Loading**: Load instruction files for batch execution.

## 🖱️ How to Use the GUI

### 📋 Main Sections

1. **Memory Panel**:
   - Displays memory addresses, binary values, and hexadecimal values.
   - **Clear Memory** button to reset memory contents to zero.

2. **Register Panel**:
   - Shows register addresses and corresponding values in integer and floating-point formats.
   - **Clear Register** button to reset register contents.

3. **Instruction and Program Controls**:
   - **Instruction**: Input an instruction manually and press **Store** to save it in memory.
   - **Starting Address**: Set the starting address of the program, then press **Fetch** to load instructions from memory.
   - **Program Counter**: Displays the current execution address.

4. **Execution Controls**:
   - **Run One Cycle**: Executes the next instruction in memory based on the program counter.
   - **Run**: Executes instructions continuously until a halt instruction is encountered.
   - **Add File**: Load a file with instructions for batch execution.

5. **Output Screen**:
   - Shows the results of executed instructions in ASCII and hexadecimal formats, allowing for easy debugging and verification.

### 🛠️ Running the Simulation

1. **Load Instructions**:
   - Manually enter instructions or load them from a file using the **Add File** button.

2. **Set Program Counter**:
   - Enter the starting memory address in **Starting Address** and click **Fetch**.

3. **Execute Instructions**:
   - For single-step execution, use **Run One Cycle**.
   - To execute the full program, click **Run**.

4. **View Output**:
   - Check the **Output Screen** for results in ASCII, hex, and other formats. The results include both numeric and character representations, which helps with debugging.

5. **Reset as Needed**:
   - Use **Clear Memory** and **Clear Register** to reset the memory and registers to their initial states.

## 📂 Example Usage

1. **Load File**: Click **Add File** and select a text file with machine instructions.
2. **Set Start Address**: Enter a valid address in the **Starting Address** field and click **Fetch**.
3. **Execute Program**: Choose **Run** for continuous execution or **Run One Cycle** for step-by-step control.
4. **Check Results**: The **Output Screen** displays program output, showing values in multiple formats (ASCII, hex, integer, float) for easy interpretation.

