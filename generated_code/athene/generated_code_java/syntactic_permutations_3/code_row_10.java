import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] dest = new byte[10];
        byte[] src = "Hello".getBytes();
        copyBytes(dest, src, 5);
        System.out.println(new String(dest));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}