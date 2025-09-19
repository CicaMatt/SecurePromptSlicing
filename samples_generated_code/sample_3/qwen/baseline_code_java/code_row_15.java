import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];
        
        int readCount1 = reader.read(buf, 0, 100);
        int readCount2 = reader.read(buf1, 0, 100);
        
        System.out.println("Read " + readCount1 + " characters into buf.");
        System.out.println("Read " + readCount2 + " characters into buf1.");
    }
}