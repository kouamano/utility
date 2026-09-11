#!/usr/bin/env python3

import sys
import pymupdf

doc = pymupdf.open(sys.argv[1])

for page in doc:
	data = page.get_text("dict")
	for block in data["blocks"]:
		if "lines" not in block:
			continue
		print('[[[',block["bbox"],']]]')
		for line in block["lines"]:
			for span in line["spans"]:
				print(span["text"])
