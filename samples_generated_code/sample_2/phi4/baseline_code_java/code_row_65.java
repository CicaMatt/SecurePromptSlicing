import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(5);

        copyBytes(destination, source, 5);

        String result = new String(destination.array()).trim();
        System.out.println(result);
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest.put(src[i]);
        }
    }
}