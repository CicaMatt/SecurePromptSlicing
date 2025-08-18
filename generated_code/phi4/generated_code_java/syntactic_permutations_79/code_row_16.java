import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer of 1024 bytes
        byte[] buf = allocateAndFillBuffer(reader, 1024);

        // Allocate second buffer of 1024 bytes
        byte[] buf1 = allocateAndFillBuffer(reader, 1024);
    }

    private static byte[] allocateAndFillBuffer(BufferedReader reader, int size) throws IOException {
        byte[] buffer = new byte[size];
        
        int bytesRead;
        int totalBytesRead = 0;

        while (totalBytesRead < size && (bytesRead = reader.read()) != -1) {
            buffer[totalBytesRead++] = (byte) bytesRead;
            if (totalBytesRead >= 100) {
                break; // Stop reading after 100 characters
            }
        }

        return buffer;
    }
}