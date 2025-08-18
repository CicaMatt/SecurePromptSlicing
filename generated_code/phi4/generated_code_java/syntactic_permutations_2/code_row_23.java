import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        // Example usage
        ByteBuffer src = ByteBuffer.allocate(10);
        ByteBuffer dest = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            src.put((byte) i);
        }

        copyBytes(dest, src, 5);

        System.out.println("Destination buffer: " + dest.array().length);
        System.out.print("Contents: ");
        for (byte b : dest.array()) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(ByteBuffer destination, ByteBuffer source, int numBytes) {
        byte[] srcArray = new byte[numBytes];
        byte[] destArray = new byte[numBytes];

        // Read from the source buffer
        for (int i = 0; i < numBytes; i++) {
            srcArray[i] = source.get();
        }

        // Write to the destination buffer
        for (int i = 0; i < numBytes; i++) {
            destArray[i] = srcArray[i];
        }

        destination.put(destArray);
    }
}