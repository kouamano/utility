#!/usr/bin/env python3

# config start
pgRECTS = '!![['
pgRECTE = ']]'
blDLM = '>>>'
bbS = '[[['
bbE = ']]]'
txS = '{{{'
txE = '}}}'
# config end

import sys
import pymupdf

doc = pymupdf.open(sys.argv[1])

for page in doc:
	data = page.get_text("dict")
	print(pgRECTS,page.rect,pgRECTE)
	for block in data["blocks"]:
		print(blDLM)
		if "lines" not in block:
			continue
		print(bbS,block["bbox"],bbE)
		for line in block["lines"]:
			print(txS)
			for span in line["spans"]:
				print(span["text"])
			print(txE)
