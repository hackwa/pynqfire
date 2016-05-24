
################################################################
# This is a generated script based on design: zybo
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.4
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source zybo_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7z010clg400-2

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name zybo

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set DDR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR ]
  set FIXED_IO [ create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO ]

  # Create ports

  # Create instance: axi_ic_ps7_M_AXI_GP0, and set properties
  set axi_ic_ps7_M_AXI_GP0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_ic_ps7_M_AXI_GP0 ]
  set_property -dict [ list \
CONFIG.M00_HAS_REGSLICE {1} \
CONFIG.NUM_MI {1} \
CONFIG.NUM_SI {1} \
CONFIG.S00_HAS_REGSLICE {1} \
CONFIG.STRATEGY {0} \
 ] $axi_ic_ps7_M_AXI_GP0

  # Create instance: cpp_FIR_0, and set properties
  set cpp_FIR_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:cpp_FIR:1.0 cpp_FIR_0 ]

  # Create instance: cpp_FIR_0_if, and set properties
  set cpp_FIR_0_if [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_accelerator_adapter:2.1 cpp_FIR_0_if ]
  set_property -dict [ list \
CONFIG.C_INPUT_SCALAR_0_WIDTH {32} \
CONFIG.C_N_INPUT_ARGS {0} \
CONFIG.C_N_INPUT_SCALARS {1} \
CONFIG.C_N_OUTPUT_ARGS {0} \
CONFIG.C_N_OUTPUT_SCALARS {1} \
CONFIG.C_OSCALAR_0_MODE {AP_VLD} \
CONFIG.C_OUTPUT_SCALAR_0_WIDTH {32} \
 ] $cpp_FIR_0_if

  # Create instance: cpp_FIR_0_ret, and set properties
  set cpp_FIR_0_ret [ create_bd_cell -type ip -vlnv xilinx.com:ip:ovld_reg:1.0 cpp_FIR_0_ret ]
  set_property -dict [ list \
CONFIG.DATA_WIDTH {32} \
 ] $cpp_FIR_0_ret

  # Create instance: proc_sys_reset_0, and set properties
  set proc_sys_reset_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_0 ]

  # Create instance: proc_sys_reset_1, and set properties
  set proc_sys_reset_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_1 ]

  # Create instance: proc_sys_reset_2, and set properties
  set proc_sys_reset_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_2 ]

  # Create instance: proc_sys_reset_3, and set properties
  set proc_sys_reset_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_3 ]

  # Create instance: ps7, and set properties
  set ps7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 ps7 ]
  set_property -dict [ list \
CONFIG.PCW_EN_CLK1_PORT {1} \
CONFIG.PCW_EN_CLK2_PORT {1} \
CONFIG.PCW_EN_CLK3_PORT {1} \
CONFIG.PCW_FCLK1_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FCLK2_PERIPHERAL_CLKSRC {IO PLL} \
CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {25} \
CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {100} \
CONFIG.PCW_FPGA2_PERIPHERAL_FREQMHZ {125} \
CONFIG.PCW_FPGA3_PERIPHERAL_FREQMHZ {50} \
CONFIG.PCW_I2C0_PERIPHERAL_ENABLE {0} \
CONFIG.PCW_IMPORT_BOARD_PRESET {ZYBO_zynq_def.xml} \
CONFIG.PCW_IRQ_F2P_INTR {1} \
CONFIG.PCW_QSPI_PERIPHERAL_ENABLE {1} \
CONFIG.PCW_USB0_PERIPHERAL_ENABLE {0} \
CONFIG.PCW_USE_FABRIC_INTERRUPT {1} \
CONFIG.PCW_USE_M_AXI_GP0 {1} \
 ] $ps7

  # Create instance: ps7_irq_const, and set properties
  set ps7_irq_const [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 ps7_irq_const ]
  set_property -dict [ list \
CONFIG.CONST_VAL {0} \
CONFIG.CONST_WIDTH {1} \
 ] $ps7_irq_const

  # Create instance: xlconcat, and set properties
  set xlconcat [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat ]
  set_property -dict [ list \
CONFIG.NUM_PORTS {1} \
 ] $xlconcat

  # Create interface connections
  connect_bd_intf_net -intf_net axi_ic_ps7_M_AXI_GP0_M00_AXI [get_bd_intf_pins axi_ic_ps7_M_AXI_GP0/M00_AXI] [get_bd_intf_pins cpp_FIR_0_if/S_AXI]
  connect_bd_intf_net -intf_net cpp_FIR_0_if_AP_CTRL [get_bd_intf_pins cpp_FIR_0/ap_ctrl] [get_bd_intf_pins cpp_FIR_0_if/AP_CTRL]
connect_bd_intf_net -intf_net [get_bd_intf_nets cpp_FIR_0_if_AP_CTRL] [get_bd_intf_pins cpp_FIR_0_if/AP_CTRL] [get_bd_intf_pins cpp_FIR_0_ret/AP_CTRL]
  connect_bd_intf_net -intf_net ps7_DDR [get_bd_intf_ports DDR] [get_bd_intf_pins ps7/DDR]
  connect_bd_intf_net -intf_net ps7_FIXED_IO [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins ps7/FIXED_IO]
  connect_bd_intf_net -intf_net ps7_M_AXI_GP0 [get_bd_intf_pins axi_ic_ps7_M_AXI_GP0/S00_AXI] [get_bd_intf_pins ps7/M_AXI_GP0]

  # Create port connections
  connect_bd_net -net clkid0 [get_bd_pins proc_sys_reset_0/slowest_sync_clk] [get_bd_pins ps7/FCLK_CLK0]
  connect_bd_net -net clkid1 [get_bd_pins axi_ic_ps7_M_AXI_GP0/ACLK] [get_bd_pins axi_ic_ps7_M_AXI_GP0/M00_ACLK] [get_bd_pins axi_ic_ps7_M_AXI_GP0/S00_ACLK] [get_bd_pins cpp_FIR_0/ap_clk] [get_bd_pins cpp_FIR_0_if/aclk] [get_bd_pins cpp_FIR_0_if/s_axi_aclk] [get_bd_pins cpp_FIR_0_ret/clk] [get_bd_pins proc_sys_reset_1/slowest_sync_clk] [get_bd_pins ps7/FCLK_CLK1] [get_bd_pins ps7/M_AXI_GP0_ACLK]
  connect_bd_net -net clkid2 [get_bd_pins proc_sys_reset_2/slowest_sync_clk] [get_bd_pins ps7/FCLK_CLK2]
  connect_bd_net -net clkid3 [get_bd_pins proc_sys_reset_2/dcm_locked] [get_bd_pins proc_sys_reset_3/slowest_sync_clk] [get_bd_pins ps7/FCLK_CLK3]
  connect_bd_net -net cpp_FIR_0_if_ap_iscalar_0_dout [get_bd_pins cpp_FIR_0/x] [get_bd_pins cpp_FIR_0_if/ap_iscalar_0_dout]
  connect_bd_net -net cpp_FIR_0_if_aresetn [get_bd_pins cpp_FIR_0/ap_rst_n] [get_bd_pins cpp_FIR_0_if/aresetn]
  connect_bd_net -net cpp_FIR_0_ret1 [get_bd_pins cpp_FIR_0/ret] [get_bd_pins cpp_FIR_0_ret/data_in]
  connect_bd_net -net cpp_FIR_0_ret_ap_vld [get_bd_pins cpp_FIR_0/ret_ap_vld] [get_bd_pins cpp_FIR_0_ret/vld_in]
  connect_bd_net -net cpp_FIR_0_ret_data_out [get_bd_pins cpp_FIR_0_if/ap_oscalar_0_din] [get_bd_pins cpp_FIR_0_ret/data_out]
  connect_bd_net -net cpp_FIR_0_ret_vld_out [get_bd_pins cpp_FIR_0_if/ap_oscalar_0_vld] [get_bd_pins cpp_FIR_0_ret/vld_out]
  connect_bd_net -net proc_sys_reset_1_interconnect_aresetn [get_bd_pins axi_ic_ps7_M_AXI_GP0/ARESETN] [get_bd_pins axi_ic_ps7_M_AXI_GP0/M00_ARESETN] [get_bd_pins axi_ic_ps7_M_AXI_GP0/S00_ARESETN] [get_bd_pins proc_sys_reset_1/interconnect_aresetn]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins cpp_FIR_0_if/s_axi_aresetn] [get_bd_pins proc_sys_reset_1/peripheral_aresetn]
  connect_bd_net -net ps7_FCLK_RESET0_N [get_bd_pins proc_sys_reset_0/ext_reset_in] [get_bd_pins proc_sys_reset_1/ext_reset_in] [get_bd_pins proc_sys_reset_2/ext_reset_in] [get_bd_pins proc_sys_reset_3/ext_reset_in] [get_bd_pins ps7/FCLK_RESET0_N]
  connect_bd_net -net ps7_irq_const_dout [get_bd_pins ps7_irq_const/dout] [get_bd_pins xlconcat/In0]
  connect_bd_net -net xlconcat_dout [get_bd_pins ps7/IRQ_F2P] [get_bd_pins xlconcat/dout]

  # Create address segments
  create_bd_addr_seg -range 0x10000 -offset 0x43C00000 [get_bd_addr_spaces ps7/Data] [get_bd_addr_segs cpp_FIR_0_if/S_AXI/Reg] SEG_cpp_FIR_0_if_Reg

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.4.10  2014-10-02 bk=1.3207 VDI=35 GEI=35 GUI=JA:1.8
#  -string -flagsOSRD
preplace port DDR -pg 1 -y 340 -defaultsOSRD
preplace port FIXED_IO -pg 1 -y 360 -defaultsOSRD
preplace inst ps7 -pg 1 -lvl 2 -y 410 -defaultsOSRD
preplace inst proc_sys_reset_0 -pg 1 -lvl 3 -y 80 -defaultsOSRD
preplace inst proc_sys_reset_1 -pg 1 -lvl 3 -y 250 -defaultsOSRD
preplace inst xlconcat -pg 1 -lvl 1 -y 410 -defaultsOSRD
preplace inst proc_sys_reset_2 -pg 1 -lvl 3 -y 450 -defaultsOSRD
preplace inst proc_sys_reset_3 -pg 1 -lvl 3 -y 620 -defaultsOSRD
preplace netloc ps7_FIXED_IO 1 2 2 590 360 NJ
preplace netloc ps7_DDR 1 2 2 570 340 NJ
preplace netloc clkid0 1 2 1 560
preplace netloc xlconcat_dout 1 1 1 N
preplace netloc clkid1 1 2 1 580
preplace netloc clkid2 1 2 1 610
preplace netloc clkid3 1 2 1 610
preplace netloc ps7_FCLK_RESET0_N 1 2 1 600
levelinfo -pg 1 0 100 380 780 980
",
}

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


