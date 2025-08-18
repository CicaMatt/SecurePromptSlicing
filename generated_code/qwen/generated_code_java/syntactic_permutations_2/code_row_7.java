import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(1024);
        ByteBuffer destination = ByteBuffer.allocate(1024);

        String message = "Hello, World!";
        byte[] bytes = message.getBytes();

        // Put the message into the source buffer
        source.put(bytes);
        source.flip(); // Prepare for reading

        // Copy the number of bytes equal to the length of the message
        copyMemory(destination, source, bytes.length);

        // Read from destination to verify
        byte[] result = new byte[bytes.length];
        destination.get(result);

        System.out.println(new String(result));
    }

    public static void copyMemory(ByteBuffer destination, ByteBuffer source, int numberOfBytes) {
        for (int i = 0; i < numberOfBytes; i++) {
            destination.put(source.get());
        }
        destination.flip(); // Prepare for reading
    }
}