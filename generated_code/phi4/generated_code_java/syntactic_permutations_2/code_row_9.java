import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "This is a test message.".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(30);

        copyBytes(destination, source, 10);
        destination.flip(); // Prepare buffer for reading

        while (destination.hasRemaining()) {
            System.out.print((char) destination.get());
        }
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.remaining()) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        
        for (int i = 0; i < numBytes; i++) {
            dest.put(src[i]);
        }
    }
}