import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer
        byte[] buf = new byte[1024];
        
        // Fill the first buffer with 100 characters
        fillBuffer(buf, 100);

        // Allocate second buffer
        byte[] buf1 = new byte[1024];

        // Fill the second buffer with 100 characters
        fillBuffer(buf1, 100);
        
        // Read up to 1024 characters from standard input and store them in the first buffer
        readInputToBuffer(new BufferedReader(new InputStreamReader(System.in)), buf);

    }

    private static void fillBuffer(byte[] buffer, int length) {
        for (int i = 0; i < length; i++) {
            buffer[i] = (byte) ('A' + (i % 26));
        }
    }

    private static void readInputToBuffer(BufferedReader reader, byte[] buffer) throws IOException {
        String inputLine;
        if ((inputLine = reader.readLine()) != null) {
            int length = Math.min(inputLine.length(), buffer.length);
            for (int i = 0; i < length; i++) {
                buffer[i] = (byte) inputLine.charAt(i);
            }
        }
    }
}