#!/usr/bin/env python3
"""Write the data file for the interactive layer page (docs/index.html).

It holds the expanded layers from keymap.c and the board's physical layout from the QMK API,
as a script so the page also works when opened straight from disk.

Usage: page_data.py <keymap.c> <qmk keyboard> <board id> <board name> > docs/data/<board id>.js
"""
import json
import sys
import urllib.request

from keymap_to_json import expand_keymap


def main(path, keyboard, board_id, board_name):
    order, layers = expand_keymap(path)
    with urllib.request.urlopen(f"https://keyboards.qmk.fm/v1/keyboards/{keyboard}/info.json") as r:
        info = json.load(r)["keyboards"][keyboard]
    geometry = [
        {k: key[k] for k in ("x", "y", "w", "h", "r", "rx", "ry") if k in key}
        for key in info["layouts"]["LAYOUT"]["layout"]
    ]
    data = {
        "name": board_name,
        "keyboard": keyboard,
        "layers": [{"id": n.removeprefix("U_"), "keys": layers[n]} for n in order],
        "geometry": geometry,
    }
    print("window.KEYMAPS = window.KEYMAPS || {};")
    print(f"window.KEYMAPS[{json.dumps(board_id)}] = {json.dumps(data, ensure_ascii=False)};")


if __name__ == "__main__":
    main(*sys.argv[1:5])
