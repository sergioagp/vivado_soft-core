# vivado_soft-core
This repository contains a Vivado project and software project designed for testing, programming, and deploying code into a soft-core processor in a Zynq UltraScale+ (US+) device.

## How to Use
Clone the repository:

> git clone https://github.com/your-username/vivado_soft-core.git
> cd vivado_soft-core


Open Vivado and source the project Tcl script:
> vivado -source vivado_project.tcl
This will create and open the Vivado project with the specified IP cores and constraints.
Follow the Vivado toolflow to synthesize, implement, and generate the bitstream.

Export the hardware to the SDK and launch the SDK.

Compile the soft-core test example located in the src/soft-core/aes-example

Test the AES example using the `cortex-debug` VS CODE extension and QEMU

Import the software project located in the src/apu directory into the SDK.

Build the software project and program the generated bitstream onto the Zynq US+ device.

Run the application on the soft-core processor.

## Additional Information
The ip_repo directory contains IP cores for the ARM Cortex-M1 processor and DAPLink to Arty shield.

The src/soft-core directory contains source code for an example soft-core processor application, including the main AES example.

The vivado_project.tcl script automates the creation of the Vivado project with the specified IP cores and constraints.

Feel free to explore the subdirectories for more detailed information on each component of the project. If you encounter any issues or have questions, please refer to the provided documentation or open an issue on GitHub.

