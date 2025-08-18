import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String src = "Hello";
        byte[] srcBytes = src.getBytes();
        ByteBuffer dest = ByteBuffer.allocate(10);

        copyMemory(srcBytes, 0, dest, 0, srcBytes.length);

        System.out.println(new String(dest.array()));
    }

    public static void copyMemory(byte[] source, int srcOffset, ByteBuffer destination, int destOffset, int length) {
        for (int i = 0; i < length; i++) {
            destination.put(destOffset + i, source[srcOffset + i]);
        }
    }
}