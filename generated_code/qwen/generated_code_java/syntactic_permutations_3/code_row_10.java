import java.nio.ByteBuffer;

public class ByteCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] source = sourceString.getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination length.");
        }
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}