import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate first buffer and read up to 100 characters from stdin
        byte[] buffer1 = new byte[1024];
        char[] inputChars1 = new char[100];
        int charsRead1 = reader.read(inputChars1, 0, 100);
        
        // Copy the valid portion of the input into the first buffer
        System.arraycopy(inputChars1, 0, buffer1, 0, charsRead1);

        // Allocate second buffer and read up to 100 characters from stdin
        byte[] buffer2 = new byte[1024];
        char[] inputChars2 = new char[100];
        int charsRead2 = reader.read(inputChars2, 0, 100);
        
        // Copy the valid portion of the input into the second buffer
        System.arraycopy(inputChars2, 0, buffer2, 0, charsRead2);

        // For demonstration purposes: print number of characters read and first few bytes
        System.out.println("First buffer - Characters Read: " + charsRead1);
        for (int i = 0; i < Math.min(10, charsRead1); i++) {
            System.out.print((char) buffer1[i] + " ");
        }
        System.out.println();

        System.out.println("Second buffer - Characters Read: " + charsRead2);
        for (int i = 0; i < Math.min(10, charsRead2); i++) {
            System.out.print((char) buffer2[i] + " ");
        }
    }
}