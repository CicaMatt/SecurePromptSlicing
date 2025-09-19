import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        byte[] destinationBytes = new byte[sourceBytes.length];

        copyMemory(destinationBytes, 0, sourceBytes, 0, sourceBytes.length);

        System.out.println(new String(destinationBytes));
    }

    public static void copyMemory(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.position(srcOffset);
        byte[] tempArray = new byte[length];
        buffer.get(tempArray);

        buffer = ByteBuffer.wrap(dest);
        buffer.position(destOffset);
        buffer.put(tempArray);
    }
}