import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] destination = new byte[sourceString.getBytes().length];

        copyBytes(destination, sourceString.getBytes(), sourceString.getBytes().length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}