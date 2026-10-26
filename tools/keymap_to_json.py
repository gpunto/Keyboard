#!/usr/bin/env python3
"""Turn a miryoku_g keymap.c into a QMK keymap.json that keymap-drawer can parse.

QMK's own `qmk c2json` can't follow the LAYOUT_miryoku wrapper or the X-macro layer list,
so this runs the C preprocessor on the keymap itself and reads the expanded layers.

Usage: keymap_to_json.py <keymap.c> <keyboard> > keymap.json
"""
import json
import re
import subprocess
import sys


def split_args(s):
    """Split a macro argument list on top-level commas."""
    args, depth, cur = [], 0, ""
    for ch in s:
        if ch == "," and depth == 0:
            args.append(cur.strip())
            cur = ""
            continue
        depth += ch == "("
        depth -= ch == ")"
        cur += ch
    if cur.strip():
        args.append(cur.strip())
    return args


def expand_keymap(path):
    """Return (layer names in index order, {name: [raw keycodes]}) with the U_ prefix kept."""
    src = open(path).read().replace("#include QMK_KEYBOARD_H", "")
    # Mark each LAYOUT(...) call so the expanded keys are easy to find
    src = "#define LAYOUT(...) @@LAYOUT(__VA_ARGS__)@@\n#define _______ KC_TRNS\n" + src
    out = subprocess.run(["cc", "-E", "-P", "-x", "c", "-"], input=src, capture_output=True, text=True, check=True).stdout

    names = re.search(r"enum\s+layer_names\s*\{([^}]*)\}", out).group(1)
    order = [n.strip() for n in names.split(",") if n.strip()]
    layers = {}
    for m in re.finditer(r"\[\s*(U_\w+)\s*\]\s*=\s*@@LAYOUT\((.*?)\)@@", out, re.S):
        layers[m.group(1)] = [re.sub(r"\s+", "", key) for key in split_args(m.group(2))]
    return order, layers


def main(path, keyboard):
    order, layers = expand_keymap(path)
    index = {n: i for i, n in enumerate(order)}
    # Layer references by number, the way QMK's own keymap.json has them
    numbered = lambda key: re.sub(r"\b(LT|MO|TG|TO|DF|OSL)\((U_\w+)", lambda k: f"{k.group(1)}({index[k.group(2)]}", key)
    json.dump(
        {
            "keyboard": keyboard,
            "keymap": "miryoku_g",
            "layout": "LAYOUT",
            "layer_names": [n.removeprefix("U_") for n in order],
            "layers": [[numbered(key) for key in layers[n]] for n in order],
        },
        sys.stdout,
        indent=1,
    )


if __name__ == "__main__":
    main(*sys.argv[1:3])
