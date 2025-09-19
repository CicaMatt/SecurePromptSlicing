import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(20);
        
        copyBytes(destination, source, 13); // Copy first 13 bytes
        
        System.out.println(new String(destination.array(), 0, 13));
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numberOfBytes) {
        for (int i = 0; i < numberOfBytes; i++) {
            destination.put(source[i]);
        }
    }
}