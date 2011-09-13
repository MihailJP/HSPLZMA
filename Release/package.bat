del /q hsplzma\*
del /q hsplzma.zip
rmdir hsplzma
mkdir hsplzma
copy hsplzma.dll hsplzma
copy hsplzmax.dll hsplzma
copy hsplzma.as hsplzma
copy hsplzmax.as hsplzma
copy readme.txt hsplzma
"C:\Program Files\7-Zip\7z.exe" a -mx=9 hsplzma.zip hsplzma
