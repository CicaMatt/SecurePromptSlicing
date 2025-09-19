import java.io.IOException;
import java.nio.ByteBuffer;

public class BufferExample {

    public static void main(String[] args) {
        ByteBuffer buf = allocateBuffer(1024);
        try {
            readFromStandardInput(buf, 10);
        } catch (IOException e) {
            System.err.println("Error reading from standard input: " + e.getMessage());
        }
        
        // Print the content of the buffer to verify
        byte[] data = new byte[buf.position()];
        buf.flip(); // Flip for read mode
        buf.get(data, 0, data.length);
        System.out.println(new String(data));
    }

    public static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }

    public static void readFromStandardInput(ByteBuffer buffer, int numChars) throws IOException {
        byte[] bytes = new byte[numChars];
        if (System.in.read(bytes, 0, numChars) != -1) {
            buffer.put(bytes);
        }
    }
}