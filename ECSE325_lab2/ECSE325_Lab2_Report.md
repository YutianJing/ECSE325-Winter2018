

# ECSE 325

### Lab 2 Report

### Lucas Bluethner 260664905

### Yutian Jing, 260680087

### March 20, 2018

<div style="page-break-after: always;"></div>

# Introduction

The purpose of this lab was to learn the basics of fix-point representations, how to convert floating point numbers into fix point numbers, how to create a VHDL testbench and test the functionality of the VHDL code (functional verification).

Specifically in this lab, a conversion program is first needed to be constructed to read floating-point input from two txt files each consists 1000 floating-point numbers, convert the numbers to fix-point representations and write to two files created by the program. A multiplication-accumulation (MAC) unit is then supposed to be implemented using the fix-point outputs from the generated files. The final step is to write up the testbench code and verify the VHDL design.

<div style="page-break-after: always;"></div>

# Code Implementation

Below is the VHDL code that implements the MAC unit.

![]()

<div style="page-break-after: always;"></div>

# Results

##Testbench Implementation

![]()

After converting the input radix format to decimal, it can be seen that the unit output from the simulation matches the calculated result from the fed input x and y, which prooves the implementation is successful.

## Compilation Report

![FlowSummary](/Users/Max/Desktop/Lab2Pictures/FlowSummary.jpg)

*Fig. 1 Compilation Report: Flow Summary*

## Resource Utilization

Analyzing the flow summary in the compilation report, it can be seen that 20 register were used in total, which is a pretty low-profile MAC unit implementation as the MAC unit only consists simple multiplier and adder logic.

## RTL View

![RTL_Viewer](/Users/Max/Desktop/Lab2Pictures/RTL_Viewer.png)

*Fig. 3 RTL View of the Circuit*

From the above RTL view, it can be seen that multiplier and adder are allocated exactly as the MAC unit diagram shown in the lab manual with feedback from the unit output.

## Grading Sheet

![GradingSheet](/Users/Max/Desktop/Lab2Pictures/GradingSheet.jpg)

*Fig. 4 Grading Sheet*

