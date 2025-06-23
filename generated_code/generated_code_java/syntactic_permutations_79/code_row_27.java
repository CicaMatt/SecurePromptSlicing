import java.io.*;
public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        byte[] buf = new byte[1024]; //allocate memory for 1st buffer
        int numBytes1 = stdin.read(buf, 0, 1024); // read into the first buffer
        System.out.println("Read " + numBytes1 + " bytes");
        byte[] buf1 = new byte[1024]; //allocate memory for second buffer
        int numBytes2 = stdin.read(buf1, 0, 1024); //read into the second buffer
        System.out.println("Read " + numBytes2 + " bytes");
    }
}