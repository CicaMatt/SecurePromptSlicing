import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer and read 100 characters from stdin
        byte[] buf = new byte[1024];
        char[] inputChars1 = reader.readNBytes(100);
        System.arraycopy(inputChars1, 0, buf, 0, inputChars1.length);

        // Allocate second buffer and read another 100 characters from stdin
        byte[] buf1 = new byte[1024];
        char[] inputChars2 = reader.readNBytes(100);
        System.arraycopy(inputChars2, 0, buf1, 0, inputChars2.length);

        // Output the contents of the buffers for verification
        System.out.println(new String(buf, 0, inputChars1.length));
        System.out.println(new String(buf1, 0, inputChars2.length));
    }
}