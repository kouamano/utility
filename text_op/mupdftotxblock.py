#!/usr/bin/env python3

PG_RECT_S = '!![['
PG_RECT_E = ']]'
BL_DLM = '>>>'
BB_S = '[[['
BB_E = ']]]'
TX_S = '{{{'
TX_E = '}}}'

import sys
import pymupdf

doc = pymupdf.open(sys.argv[1])

for page in doc:
	data = page.get_text("dict")
	print(PG_RECT_S,page.rect,PG_RECT_E)
	for block in data["blocks"]:
		print(BL_DLM)
		if "lines" not in block:
			continue
		print(BB_S,block["bbox"],BB_E)
		for line in block["lines"]:
			print(TX_S)
			for span in line["spans"]:
				print(span["text"])
			print(TX_E)
