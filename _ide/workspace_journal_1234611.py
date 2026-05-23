# 2026-05-10T18:15:25.276692
import vitis

client = vitis.create_client()
client.set_workspace(path="vitisProj")

comp = client.get_component(name="app_component")
comp.build()

comp.build()

platform = client.get_component(name="kria")
status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../../../Downloads/other1.xsa")

status = platform.build()

comp.build()

status = platform.build()

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "platform2",hw_design = "$COMPONENT_LOCATION/../../../Downloads/other1.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

platform = client.get_component(name="platform2")
status = platform.build()

comp.build()

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "platform3",hw_design = "$COMPONENT_LOCATION/../../../Downloads/other2.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

platform = client.get_component(name="platform3")
status = platform.build()

comp.build()

vitis.dispose()

