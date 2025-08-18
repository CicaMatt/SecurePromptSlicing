import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer and read data
        char[] buf = new char[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputData1 = reader.readLine();
        if (inputData1 != null && inputData1.length() > 0) {
            int charsRead = Math.min(inputData1.length(), 1024);
            System.arraycopy(inputData1.toCharArray(), 0, buf, 0, charsRead);
        }

        // Allocate second buffer and read data
        char[] buf1 = new char[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        String inputData2 = reader.readLine();
        if (inputData2 != null && inputData2.length() > 0) {
            int charsRead = Math.min(inputData2.length(), 1024);
            System.arraycopy(inputData2.toCharArray(), 0, buf1, 0, charsRead);
        }

        // Output contents of the buffers for verification
        System.out.println("First buffer content:");
        System.out.println(new String(buf, 0, buf.indexOf('\u0000') > -1 ? buf.indexOf('\u0000') : buf.length));
        
        System.out.println("Second buffer content:");
        System.out.println(new String(buf1, 0, buf1.indexOf('\u0000') > -1 ? buf1.indexOf('\u0000') : buf1.length));
    }
}