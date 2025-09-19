import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];

        System.arraycopy(source, 0, destination, 0, Math.min(source.length, destination.length));
        
        // Print the copied data
        String result = new String(destination).trim();
        System.out.println(result);
    }
}