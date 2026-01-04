import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gio

icon_theme = Gtk.IconTheme.get_default()
all_apps = Gio.AppInfo.get_all()

def search():
    for app in all_apps:
        if not app.should_show():
            continue
        
        name = app.get_display_name()
        exec_path = app.get_executable()
        icon = app.get_icon()
        icon_path = None
        
        if icon:
            if hasattr(icon, 'get_names'):
                for icon_name in icon.get_names():
                    icon_info = icon_theme.lookup_icon(icon_name, 1024, Gtk.IconLookupFlags.FORCE_SIZE)
                    if icon_info:
                        icon_path = icon_info.get_filename()
                        break
            elif hasattr(icon, 'get_file'):
                icon_path = icon.get_file().get_path()
        
        if not icon_path or not exec_path:
            continue
        
        print(f"{name},{exec_path},{icon_path}")

search()