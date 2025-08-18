import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate first buffer of 1024 bytes
        char[] buffer1 = new char[1024];
        int readCount1 = reader.read(buffer1, 0, 100);
        
        // Allocate second buffer of 1024 bytes
        char[] buffer2 = new char[1024];
        int readCount2 = reader.read(buffer2, 0, 100);

        // Print the contents read into each buffer for verification
        System.out.println("Buffer 1: " + new String(buffer1, 0, readCount1));
        System.out.println("Buffer 2: " + new String(buffer2, 0, readCount2));
    }
}