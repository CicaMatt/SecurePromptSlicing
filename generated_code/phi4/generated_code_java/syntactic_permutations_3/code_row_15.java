import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        String message = "Hello";
        byte[] sourceBytes = message.getBytes();
        int numberOfBytesToCopy = 5; // Length of "Hello"
        
        ByteBuffer buffer = ByteBuffer.allocate(numberOfBytesToCopy);
        copyMemory(buffer, sourceBytes, numberOfBytesToCopy);

        System.out.println(new String(buffer.array(), 0, numberOfBytesToCopy));
    }

    public static void copyMemory(ByteBuffer destination, byte[] source, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            destination.put(source[i]);
        }
    }
}