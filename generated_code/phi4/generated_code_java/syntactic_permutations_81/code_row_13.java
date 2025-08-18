import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        
        try {
            readData(buf, 10);
        } catch (IOException e) {
            System.out.println("Error reading data: " + e.getMessage());
        }
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readData(byte[] buf, int numChars) throws IOException {
        if (buf.length < numChars) {
            throw new IllegalArgumentException("Buffer is too small to hold the data.");
        }

        // Simulating reading 10 characters
        String sampleText = "HelloWorld"; // Example text
        for (int i = 0; i < Math.min(numChars, sampleText.length()); i++) {
            buf[i] = sampleText.charAt(i);
        }
        
        System.out.println("Data read: " + new String(buf, 0, numChars));
    }
}