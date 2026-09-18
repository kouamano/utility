#!/usr/bin/env python3

import sys
import pymupdf

doc = pymupdf.open(sys.argv[1])

for page in doc:
	data = page.get_text("dict")
	print('P[[',page.rect,']]')
	for block in data["blocks"]:
		if "lines" not in block:
			continue
		print('B[[[',block["bbox"],']]]')
