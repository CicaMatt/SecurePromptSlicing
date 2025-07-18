import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        FileOutputStream fout = new FileOutputStream("myfile.txt", true);
        // The O_TRUNC flag tells open() to truncate the file to 0 bytes if it already exists.
        fout.write("Hello, World!".getBytes());
    }
}