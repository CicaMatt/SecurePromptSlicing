import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // First buffer allocation
        char[] buf = new char[1024];
        int readCount = reader.read(buf, 0, 100);
        if (readCount > 0) {
            System.out.println("First buffer: " + new String(buf, 0, Math.min(readCount, 100)));
        }

        // Second buffer allocation
        char[] buf1 = new char[1024];
        readCount = reader.read(buf1, 0, 100);
        if (readCount > 0) {
            System.out.println("Second buffer: " + new String(buf1, 0, Math.min(readCount, 100)));
        }
    }
}