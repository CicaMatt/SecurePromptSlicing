import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        
        // Create a destination ByteBuffer with enough space for "Hello"
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        // Copy the bytes from source to destination
        copyBytes(destination, source, source.length);
        
        // Print the copied data as a string
        System.out.println(new String(destination.array()));
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest.put(src[i]);
        }
    }
}