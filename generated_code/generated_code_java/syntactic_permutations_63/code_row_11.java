package io.github.ocelot;

import java.io.*;
import java.util.zip.CRC32;

public class CalculateCheckSum {
    public static void main(String[] args) throws IOException {
        // Read buffer from file
        byte[] buffer = new byte[10];
        try (InputStream input = new FileInputStream("buffer.dat")) {
            int read = 0;
            while (read < buffer.length && ((read += input.read(buffer, read, buffer.length - read)) != -1));
        }
    
        // Calculate checksum of buffer
        CRC32 crc32 = new CRC32();
        crc32.update(buffer);
        long checksum = crc32.getValue();
        
        // Write to file if not empty
        try (OutputStream output = new FileOutputStream("checksum.dat")) {
            if (checksum != 0) {
                output.write(Long.toString(read).getBytes());
                output.write(' ');
                output.write(Long.toString(checksum).getBytes());
            }
        }
    }
}