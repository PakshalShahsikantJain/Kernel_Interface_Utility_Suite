# Kernel_Interface_Utility_Suite

This project is a custom-built Kernel Interface Utility Suite that programmatically implements major Linux commands using native system calls.<br>

Instead of relying on existing GNU utilities, we developed our own versions of important commands to understand their internal working at the OS level.<br>

All commands are enhanced with additional features for improved user interaction and customization.<br>

The executables are integrated into the system path, replacing default utilities for learning purposes, and each command is uniquely identified with the<br> postfix letter "x" (e.g., lsx, pwdx, cpx).<br>

This project demonstrates deep understanding of Linux internals, system calls, file systems, and process management.<br>

# Key Features

# Core Linux Commands Implemented

• pwdx – Print working directory<br>
• lsx – List directory contents<br>
• mkdirx – Create directory<br>
• rmx – Remove Files/directories<br>
• cpx – Copy Files<br>
• mvx – Move/Rename Files<br>
• catx – Display File contents<br>
• touchx – Create empty File<br>
• chmodx – Change File permissions<br>
• statx – Display File metadata<br>
• headx – Display First N lines<br>
• tailx – Display last N lines<br>
• wcx – Word/line/character count<br>

# Native System Call Usage

Instead of using library-level functions, this suite is implemented using low-level system calls such as:

• open()<br>
• read()<br>
• write()<br>
• close()<br>
• stat()<br>
• lstat()<br>
• mkdir()<br>
• unlink()<br>
• rmdir()<br>
• chmod()<br>
• fork()<br>
• exec()<br>
• wait()<br>
• opendir()<br>
• readdir()<br>

This provides complete control over file handling, process creation, and directory traversal.

# Advanced Custom Features

• Improved error handling and descriptive logging<br>
• Input validation for safer execution<br>
• Additional flags not available in default commands<br>
• Modular code structure<br>
• Standardized argument parsing<br>
• Robust edge-case handling<br>

# System-Level Integration

• All executables compiled and placed in system path<br>
• Commands usable directly from terminal<br>
• Postfix naming convention (x)<br>
• Executable permissions properly managed<br>

# Architecture Design

• Modular implementation (one command per file)<br>
• Common utility module for shared functions<br>
• System call abstraction where required<br>
• Structured error reporting<br>

# Learning Outcomes

• Deep understanding of Linux system calls<br>
• Clear knowledge of how Linux commands actually work internally<br>
• File descriptor management<br>
• Directory handling and inode concepts<br>
• Process creation and execution flow<br>
• Memory and resource management<br>
• Building real system utilities from scratch<br>
• Understanding PATH variable and executable resolution<br>
• Hands-on exposure to OS-level programming<br>