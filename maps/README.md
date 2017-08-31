# MAP File Addresses
MAP files can be read while keeping these addresses in mind.
- `0x00` - MAP file signature (3 bytes)
- `0x03` - Map Width (2 bytes)
- `0x05` - Map Height (2 bytes)
- `0x07` - Tile IDs, each ID is 1 byte.  Number of bytes to read depends on the map height and width.

All of the data is stored and read as little endian.  For example, if you wanted to store a map width of 24, you would store it as 0x1800 (0x0018).