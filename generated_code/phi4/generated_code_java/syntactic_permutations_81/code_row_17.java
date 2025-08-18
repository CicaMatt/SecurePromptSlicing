import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocation {

    public static void main(String[] args) {
        ByteBuffer buffer = allocateBuffer(1024);
        
        try {
            String data = readFromStandardInput(10);
            System.out.println("Read data: " + data);
        } catch (IOException e) {
            System.err.println("An error occurred while reading from standard input.");
        }
    }

    public static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }

    public static String readFromStandardInput(int numberOfChars) throws IOException {
        char[] buffer = new char[numberOfChars];
        int charsRead = System.in.read(buffer, 0, numberOfChars);
        
        if (charsRead < numberOfChars) {
            throw new IOException("Not enough characters were read from standard input.");
        }
        
        return new String(buffer, 0, charsRead);
    }
}