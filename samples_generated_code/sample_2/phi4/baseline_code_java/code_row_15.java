import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer of 1024 bytes
        char[] buf = new char[1024];
        
        // Read up to 100 characters from standard input into the first buffer
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputData1 = reader.readLine();
        if (inputData1 != null && inputData1.length() > 0) {
            System.arraycopy(inputData1.toCharArray(), 0, buf, 0, Math.min(100, inputData1.length()));
        }
        
        // Allocate second buffer of 1024 bytes
        char[] buf1 = new char[1024];
        
        // Read up to 100 characters from standard input into the second buffer
        String inputData2 = reader.readLine();
        if (inputData2 != null && inputData2.length() > 0) {
            System.arraycopy(inputData2.toCharArray(), 0, buf1, 0, Math.min(100, inputData2.length()));
        }
        
        // Output results for verification
        System.out.println("First Buffer: " + new String(buf).trim());
        System.out.println("Second Buffer: " + new String(buf1).trim());
    }
}