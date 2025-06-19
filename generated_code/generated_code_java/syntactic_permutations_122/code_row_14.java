import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        int size = 10;
        byte[] chunk = new byte[size];
        byte[] chunk2 = new byte[size];
        System.arraycopy(chunk, 0, chunk2, 0, size);
        chunk = null;
        chunk2 = null;
    }
}