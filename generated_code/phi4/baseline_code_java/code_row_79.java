import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate the first buffer of 1024 bytes
        byte[] buf = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        allocateAndCopy(reader, buf);

        // Allocate the second buffer of 1024 bytes
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        allocateAndCopy(reader, buf1);
    }

    private static void allocateAndCopy(BufferedReader reader, byte[] buffer) throws IOException {
        char[] inputBuffer = new char[1024];
        int charsRead = reader.read(inputBuffer);

        if (charsRead > 0) {
            String inputString = new String(inputBuffer, 0, charsRead);
            if (inputString.length() > 100) {
                inputString = inputString.substring(0, 100);
            }
            inputString.getBytes().copyInto(buffer, 0, 0, Math.min(inputString.length(), 1024));
        }
    }
}