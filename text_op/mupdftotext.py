#!/usr/bin/env python3

import sys
import pymupdf

doc = pymupdf.open(sys.argv[1])

for page in doc:
	text = page.get_text()
	print(text)
