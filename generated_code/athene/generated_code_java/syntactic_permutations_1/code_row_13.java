import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, numBytes));
    }

    public static void main(String[] args) {
        byte[] source = new byte[]{1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        copyMemory(destination, source, 3);
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}