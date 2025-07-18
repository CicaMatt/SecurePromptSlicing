import java.util.*;
public class Solution {
    public static void main(String[] args) {
        // declare a buffer
        byte[] buf = new byte[1024];
        // read up to 1024 characters from stdin and store them in the buffer
        System.in.read(buf, 0, 1024);
    }
}