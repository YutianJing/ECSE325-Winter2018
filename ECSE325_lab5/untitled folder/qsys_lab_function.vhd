LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all; 

ENTITY qsys_lab_function IS
PORT ( clock, resetn : IN STD_LOGIC;
	read, write, chipselect : IN STD_LOGIC;
	address : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
	in_data : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	out_data : OUT STD_LOGIC_VECTOR(31 DOWNTO 0) 
);
END qsys_lab_function ;

ARCHITECTURE Behavior OF qsys_lab_function IS

BEGIN

	--your code here

END Behavior;
