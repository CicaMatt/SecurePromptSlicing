import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String data = "Hello";
        byte[] byteArray = data.getBytes();
        
        ByteBuffer sourceBuffer = ByteBuffer.allocate(byteArray.length);
        sourceBuffer.put(byteArray);

        ByteBuffer destinationBuffer = ByteBuffer.allocate(byteArray.length);

        copyBytes(destinationBuffer, sourceBuffer, byteArray.length);

        // Reset position to read the copied bytes
        destinationBuffer.flip();

        byte[] result = new byte[destinationBuffer.remaining()];
        destinationBuffer.get(result);

        String resultString = new String(result);
        System.out.println("Copied string: " + resultString);
    }

    public static void copyBytes(ByteBuffer dest, ByteBuffer src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest.put(src.get());
        }
    }
}