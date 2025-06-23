import java.nio.ByteBuffer;

public class CopyBytes {
    public static void main(String[] args) {
        byte[] dest = new byte[10];
        byte[] src = new byte[]{48, 49, 50};
        copyBytes(dest, src, 3);
        System.out.println(new String(dest)); // Output: 012
    }

    private static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}