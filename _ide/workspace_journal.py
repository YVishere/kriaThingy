# 2026-05-23T14:50:12.148054
import vitis

client = vitis.create_client()
client.set_workspace(path="Kria_display_stream")

platform = client.get_component(name="platform3")
status = platform.build()

comp = client.get_component(name="app_component")
comp.build()

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "kria",hw_design = "$COMPONENT_LOCATION/../../../VivadoProjects/Kria_display_stream/hardware_display_stream.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

platform = client.get_component(name="kria")
status = platform.build()

comp.build()

client.delete_component(name="platform3")

comp = client.create_app_component(name="app",platform = "$COMPONENT_LOCATION/../kria/export/kria/kria.xpfm",domain = "standalone_psu_cortexa53_0")

comp = client.get_component(name="app")
status = comp.import_files(from_loc="", files=["/home/aditya/Kira_PCAM/vitisProj/app_component/src/app.yaml", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/helloworld.c", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/i2c.h", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/platform.c", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/platform.h", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/platform_config.h", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/vga_modes.h", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/xdpdma_video_example.c", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/xdpdma_video_example.h", "/home/aditya/Kira_PCAM/vitisProj/app_component/src/xdppsu_interrupt.c"])

client.delete_component(name="app")

comp = client.create_app_component(name="app",platform = "$COMPONENT_LOCATION/../kria/export/kria/kria.xpfm",domain = "standalone_psu_cortexa53_0")

status = comp.import_files(from_loc="", files=["/home/aditya/Desktop/vitisProjects/Kria_display_stream/app_component/src"])

comp.build()

comp.build()

comp.build()

client.delete_component(name="app")

comp = client.get_component(name="app_component")
comp.build()

