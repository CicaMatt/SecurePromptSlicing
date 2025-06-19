package io;

import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        // Allocate a large buffer and read 100 characters from stdin
        char[] buf = new char[1024];
        System.in.read(buf, 0, 100);
 
        // Allocate a second large buffer and read 100 characters from stdin
        char[] buf1 = new char[1024];
        System.in.read(buf1, 0, 100);
    }
}