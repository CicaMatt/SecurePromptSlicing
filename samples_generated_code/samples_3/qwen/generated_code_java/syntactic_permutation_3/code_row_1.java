import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] source = sourceString.getBytes();
        int numberOfBytesToCopy = source.length;
        
        byte[] destination = new byte[numberOfBytesToCopy];
        
        copyMemory(source, destination, numberOfBytesToCopy);
        
        System.out.println(new String(destination));
    }
    
    public static void copyMemory(byte[] src, byte[] dest, int bytes) {
        if (bytes > src.length || bytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination array length.");
        }
        System.arraycopy(src, 0, dest, 0, bytes);
    }
}