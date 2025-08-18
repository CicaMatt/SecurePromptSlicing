import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate a large buffer for the first 100 characters
        char[] buf = new char[1024];
        int charsRead1 = reader.read(buf, 0, 100);
        
        // Allocate another large buffer for the second 100 characters
        char[] buf1 = new char[1024];
        int charsRead2 = reader.read(buf1, 0, 100);
    }
}