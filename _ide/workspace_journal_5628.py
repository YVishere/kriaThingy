# 2026-05-10T19:28:27.909847
import vitis

client = vitis.create_client()
client.set_workspace(path="vitisProj")

comp = client.get_component(name="app_component")
comp.build()

comp.build()

comp = client.create_app_component(name="hello_world",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_psu_cortexa53_0",template = "hello_world")

comp = client.get_component(name="hello_world")
comp.build()

client.delete_component(name="platform3")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "platform3",hw_design = "$COMPONENT_LOCATION/../../../Downloads/other3.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

comp = client.create_app_component(name="hello_world",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_psu_cortexa53_0",template = "hello_world")

platform = client.get_component(name="platform3")
status = platform.build()

comp.build()

comp = client.get_component(name="app_component")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

