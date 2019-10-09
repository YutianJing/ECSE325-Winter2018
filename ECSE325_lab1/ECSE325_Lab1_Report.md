

# ECSE 325

### Lab 1 Report

### Lucas Bluethner 260664905

### Yutian Jing, 260680087

### March 2, 2018

<div style="page-break-after: always;"></div>

# Introduction

​	The purpose of this lab was to learn the basics of Quartus-II FPGA software and how to compile synchronous circuit VHDL declarations to a target FPGA. The goal was to see how the fitter of Quartus compiler maps the design onto FPGA hardware. This was done in this lab by implementing a synchronous 8-bit counter with the following specifications:

* Synchronous reset

* Up/down counting features

* Enable counting option

  <div style="page-break-after: always;"></div>

  # Code Implementation

  Below is the code we wrote to implement the synchronous 8-bit counter. The counter takes the following as inputs: a clock, the direction to count (up/down), the reset value, the enable value, and outputs the counter value. The output is the 8-bit count value.


```vhdl
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity g64_lab1 is

Port (	clk			: in std_logic;
		direction 	: in std_logic; -- count up if value is 0, count down 										                  if count is 1
		rst		    : in std_logic; -- resets count to 0 if rst is high
		enable		: in std_logic; -- enables counting option if 1, 					                                          -- count doesn't change if enable is 0 
		output		: out std_logic_vector(7 downto 0)); -- the output is 													                       -- the value of the count
end g64_lab1;

architecture behaviour of g64_lab1 is 

signal count: unsigned(7 downto 0); -- temporary signal to store the count

begin 
	process(clk)
	begin
        if (rising_edge(clk)) then -- Counts up or down by 1 once per clock cycle
            if (rst='1') then			-- Active high reset, resets the count back to zero
                count <= "00000000";
            elsif (enable = '1') then
                if (direction = '0') then 	
                        count <= count + 1;	-- count up if enable is 1 and direction is 0
                else								
                        count <= count - 1;	-- count down if enable is 1 anf direction is 1
                end if;
            else 
                count <= count;				-- if enable is 0, do not change the count
            end if;
        end if;
	end process;
output <= std_logic_vector(count);	-- set the output to the value of count,
								 -- and cast it to a std_logic_vector
end behaviour;
```
<div style="page-break-after: always;"></div>

# Results

## Compilation Report

![FlowSummary](/Users/Max/Desktop/Lab1Pictures/FlowSummary_8-bit.jpg)

*Fig. 1 Compilation Report: Flow Summary*

## Resource Utilization

​	Analyzing the flow summary in the compilation report, it can be seen that 8 register were used. The number of registers used is related with the bumber of bits of the counter. Here the counter implemented is 8-bit, thus there are 8 registers used in total. If the bitsize of the counter increase, the total register used will also increase.

## Chip Planner

![ChipPlanner](/Users/Max/Desktop/Lab1Pictures/ChipPlanner.jpg)

*Fig. 2 Chip Planner*

The physical hardware unit mapping of the FPGA is available in the chip planner of Quartus-II, the blue dot in the above figure is where the 8-bit counter design is acturally ultilized on the FPGA board. Since this is a low-profile design with only 8 registers used, the resources allocated to this design is little compared to the total capability of the hardware.

## RTL View of the Circuit

![RTL_Viewer](/Users/Max/Desktop/Lab1Pictures/RTL_Viewer.png)

*Fig. 3 RTL View of the Circuit*

The chip planner figure only provide an overview of provisions regarding the general resources used, however the details of the hardware resources that the code utilizes can only be seen using the RTL (register-transfer level) viewer of the Quartus-II software. From the above figure it can be seen that 2 adders, 4 multiplexers and 1 D-flipflop is allocated in order to ultilize the code wrote.

## Grading Sheet

![GradingSheet](/Users/Max/Desktop/Lab1Pictures/GradingSheet.jpg)

*Fig. 4 Grading Sheet*

# Conclusion

Modeling the counter in ModelSim, we were able to verify the behavior of our design. 

![Simulation](/Users/Max/Desktop/Lab1Pictures/8-bit-Counter_Simulation.png)

*Fig. 5 Simulation of the synchronous 8-bit counter in ModelSim*

From the wave, the counter is counting up or down by one in each clock cycle, which means the 8-bit counter implementation is successful.