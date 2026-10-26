#!/bin/sh
# Redraw a board's layer diagram (layers.svg, with keymap-drawer: uv tool install keymap-drawer)
# and the data for the interactive page (docs/data/<board>.js) from its keymap.c.
# Usage: tools/draw-layers.sh <keymap dir> <qmk keyboard>, e.g. tools/draw-layers.sh Sofle/miryoku_g sofle/rev1
set -eu
dir=$1
keyboard=$2
tools=$(dirname "$0")
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

python3 -I "$tools/keymap_to_json.py" "$dir/keymap.c" "$keyboard" > "$tmp/keymap.json"
names=$(python3 -I -c 'import json, sys; print(" ".join(json.load(open(sys.argv[1]))["layer_names"]))' "$tmp/keymap.json")
# shellcheck disable=SC2086
keymap -c "$tools/keymap-drawer.yaml" parse -q "$tmp/keymap.json" -l $names > "$tmp/keymap.yaml"
# keymap-drawer keeps QMK mod names on mod-tap holds; spell them out like the rest of the diagram
perl -pi -e 's/h: [LR]?CTL\b/h: Ctrl/; s/h: [LR]?ALT\b/h: Alt/; s/h: ALGR\b/h: AltGr/; s/h: [LR]?GUI\b/h: Cmd/; s/h: [LR]?SFT\b/h: Shift/' "$tmp/keymap.yaml"
keymap -c "$tools/keymap-drawer.yaml" draw "$tmp/keymap.yaml" > "$dir/layers.svg"
echo "Wrote $dir/layers.svg"

board=${dir%%/*}
id=$(echo "$board" | tr '[:upper:]' '[:lower:]')
python3 "$tools/page_data.py" "$dir/keymap.c" "$keyboard" "$id" "$board" > "$tools/../docs/data/$id.js"
echo "Wrote docs/data/$id.js"
