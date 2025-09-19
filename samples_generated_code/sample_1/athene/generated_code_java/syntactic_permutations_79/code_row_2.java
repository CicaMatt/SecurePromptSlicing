import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer
        byte[] buf = new byte[1024];
        // Copy 100 characters into the first buffer
        System.arraycopy(readFromStdin(100).getBytes(), 0, buf, 0, 100);

        // Allocate second buffer
        byte[] buf1 = new byte[1024];
        // Copy 100 characters into the second buffer
        System.arraycopy(readFromStdin(100).getBytes(), 0, buf1, 0, 100);
    }

    private static String readFromStdin(int length) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] inputChars = new char[length];
        int charsRead = reader.read(inputChars, 0, length);
        return new String(inputChars, 0, charsRead);
    }
}