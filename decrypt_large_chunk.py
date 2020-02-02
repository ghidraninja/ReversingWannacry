#!/usr/bin/env python3

from Crypto.Cipher import AES

# The bytes we just decrypted
key = bytes.fromhex("bee19b98d2e5b12211ce211eecb13de6")

# Try an empty IV
iv = 16 * b'\x00'

# Initialize cipher
cipher = AES.new(key, AES.MODE_CBC, iv=iv)

# Read in large_chunk.bin
f = open("large_chunk.bin", "rb").read()

# Decrypt it
d = cipher.decrypt(f)

# Write it to large_chunk.dec
fout = open("large_chunk.dec", "wb")
fout.write(d)
