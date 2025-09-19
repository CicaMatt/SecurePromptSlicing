import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, ByteBuffer.wrap(source), source.length);

        System.out.println(new String(destination.array()));
    }

    public static void copyBytes(ByteBuffer dest, ByteBuffer src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest.put(src.get(i));
        }
        dest.flip(); // Prepare the buffer to read from it
    }
}