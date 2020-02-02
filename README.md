# ReversingWannacry

These are the scripts and Ghidra projects for my Reversing Wannacry series:

[![](https://img.youtube.com/vi/Q90uZS3taG0/0.jpg)](https://www.youtube.com/watch?v=Q90uZS3taG0)

## Extracting the Ghidra projects and the resources

Note that the Ghidra project and the files in the resources ZIP file will probably trigger your AV!

The Ghidra projects and the DLL are in an encrypted ZIP, protected by the password "ghidra".

## Extracting the part of t.wnry

Simply run:

```
dd if=t.wnry of=encrypted_aes_key bs=1 skip=12 count=256
dd if=t.wnry of=large_chunk.bin skip=280 bs=1
```

## Importing the Ghidra projects

The Ghidra projects are exported as ZIP files. You can simply drag them into the Ghidra project screen.
