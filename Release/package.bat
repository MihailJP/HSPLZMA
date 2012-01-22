rmdir /s /q hsplzma
del /q hsplzma.zip
mkdir hsplzma
copy hsplzma.dll hsplzma
copy hsplzmax.dll hsplzma
mkdir hsplzma\common
copy hsplzma.as hsplzma\common
copy hsplzmax.as hsplzma\common
mkdir hsplzma\hsphelp
copy hsplzma.hs hsplzma\hsphelp
mkdir hsplzma\sample
mkdir hsplzma\sample\hsplzma
copy lzmaenc.hsp hsplzma\sample\hsplzma
copy readme.txt hsplzma
"C:\Program Files\7-Zip\7z.exe" a -mx=9 hsplzma.zip hsplzma
