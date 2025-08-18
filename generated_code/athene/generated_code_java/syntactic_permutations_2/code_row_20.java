import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyNumber(long dest, long src, int number) {
        ByteBuffer.wrap(new byte[] {(byte) (number & 0xFF)}).putLong(dest, ByteBuffer.wrap(new byte[] {(byte) (number & 0xFF)}).getLong(src));
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        long dest = 0;
        long src = 5;
        int number = 42;

        ByteBuffer.wrap(buffer, (int)src, 1).put((byte)(number & 0xFF));
        System.arraycopy(buffer, (int)src, buffer, (int)dest, 1);

        for (byte b : buffer) {
            System.out.print((b & 0xFF) + " ");
        }
    }
}