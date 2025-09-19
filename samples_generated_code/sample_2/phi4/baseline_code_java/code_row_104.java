import java.io.IOException;
import java.nio.ByteBuffer;

public class BufferAllocation {

    public static void main(String[] args) {
        ByteBuffer buffer = allocateBuffer(1024);
        try {
            String data = readFromStandardInput(buffer, 10);
            System.out.println("Data read: " + data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }

    private static String readFromStandardInput(ByteBuffer buffer, int numberOfChars) throws IOException {
        byte[] tempBuffer = new byte[numberOfChars];
        int bytesRead = System.in.read(tempBuffer, 0, numberOfChars);
        
        if (bytesRead > 0) {
            buffer.put(tempBuffer, 0, bytesRead);
            return new String(buffer.array(), 0, bytesRead);
        }
        
        return "";
    }
}