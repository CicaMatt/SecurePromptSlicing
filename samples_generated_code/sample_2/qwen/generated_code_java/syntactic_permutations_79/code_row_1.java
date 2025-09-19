import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        
        // First buffer allocation and read
        byte[] buf1 = new byte[bufferSize];
        System.in.read(buf1, 0, 100);

        // Second buffer allocation and read
        byte[] buf2 = new byte[bufferSize];
        System.in.read(buf2, 0, 100);
    }
}