import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer of 1024 bytes and copy in up to 100 characters from stdin
        byte[] buf = new byte[1024];
        allocateAndCopy(reader, buf);

        // Allocate second buffer of 1024 bytes and copy in up to 100 characters from stdin
        byte[] buf1 = new byte[1024];
        allocateAndCopy(reader, buf1);
    }

    private static void allocateAndCopy(BufferedReader reader, byte[] buffer) throws IOException {
        char[] tempBuffer = new char[100]; // Temporary buffer to hold the input characters
        int charsRead = reader.read(tempBuffer, 0, 100); // Read up to 100 characters from stdin

        if (charsRead > 0) {
            String inputString = new String(tempBuffer, 0, charsRead);
            inputString.getChars(0, Math.min(charsRead, buffer.length), buffer, 0); // Copy the characters into the allocated buffer
        }
    }
}