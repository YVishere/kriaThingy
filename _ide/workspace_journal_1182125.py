# 2026-05-10T17:55:40.973891
import vitis

client = vitis.create_client()
client.set_workspace(path="vitisProj")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "kria",hw_design = "$COMPONENT_LOCATION/../../Vitis/kria/hw/design_1_wrapper.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

comp = client.create_app_component(name="app_component",platform = "$COMPONENT_LOCATION/../kria/export/kria/kria.xpfm",domain = "standalone_psu_cortexa53_0")

comp = client.get_component(name="app_component")
status = comp.import_files(from_loc="", files=["/home/aditya/Kira_PCAM/Vitis/display_port_app/src/helloworld.c", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/i2c.h", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/lscript.ld", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/platform.c", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/platform.h", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/platform_config.h", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/vga_modes.h", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/xdpdma_video_example.c", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/xdpdma_video_example.h", "/home/aditya/Kira_PCAM/Vitis/display_port_app/src/xdppsu_interrupt.c"])

platform = client.get_component(name="kria")
status = platform.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

vitis.dispose()

