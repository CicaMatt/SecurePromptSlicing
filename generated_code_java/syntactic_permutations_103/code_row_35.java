import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        // Create a new file or open an existing file for writing only
        RandomAccessFile raf = new RandomAccessFile("myFile", "rw");

        // Write some data to the file
        raf.writeBytes("Hello, world!\n");

        // Close the file when finished
        raf.close();
    }
}