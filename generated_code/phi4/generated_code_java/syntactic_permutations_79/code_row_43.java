import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            allocateAndCopy(reader, buf);
            allocateAndCopy(reader, buf1);
            
            // Output the content of buffers for demonstration purposes
            System.out.println("First Buffer Content: " + new String(buf).trim());
            System.out.println("Second Buffer Content: " + new String(buf1).trim());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void allocateAndCopy(BufferedReader reader, byte[] buffer) throws IOException {
        int bytesRead = 0;
        while (bytesRead < buffer.length && (bytesRead += reader.read(buffer, bytesRead, buffer.length - bytesRead)) != -1) {}
        
        // Ensure only the first 100 characters are considered
        if (buffer.length > 100) {
            byte[] tempBuffer = new byte[100];
            System.arraycopy(buffer, 0, tempBuffer, 0, Math.min(100, bytesRead));
            System.out.println("Copied to buffer: " + new String(tempBuffer).trim());
        }
    }
}