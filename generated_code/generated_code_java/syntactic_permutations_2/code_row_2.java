import java.nio.ByteBuffer;
 
class CopyToBuffer {
    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        ByteBuffer buffer = ByteBuffer.allocate(message.length);
        copy(buffer, message, message.length);
    }
 
    private static void copy(ByteBuffer destination, byte[] source, int numberOfBytesToCopy) {
        for (int i = 0; i < numberOfBytesToCopy; i++) {
            destination.put(source[i]);
        }
    }
}