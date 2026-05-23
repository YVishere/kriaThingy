# 2026-05-19T19:28:18.534914
import vitis

client = vitis.create_client()
client.set_workspace(path="vitisProj")

comp = client.get_component(name="app_component")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

