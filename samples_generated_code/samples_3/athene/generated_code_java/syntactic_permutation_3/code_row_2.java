import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10];
        
        copyMemory(destination, source, 5);
        
        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}