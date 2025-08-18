import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        byte[] destinationBytes = new byte[sourceBytes.length];

        copyMemory(destinationBytes, sourceBytes, sourceBytes.length);

        System.out.println(new String(destinationBytes));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array");
        }
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}