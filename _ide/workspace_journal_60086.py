# 2026-05-23T13:51:51.973782
import vitis

client = vitis.create_client()
client.set_workspace(path="vitisProj")

client.delete_component(name="platform2")

client.delete_component(name="kria")

client.delete_component(name="hello_world")

comp = client.get_component(name="app_component")
comp.build()

comp.build()

vitis.dispose()

