import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceArray = sourceString.getBytes();
        byte[] destinationArray = new byte[sourceArray.length];

        copyBytes(destinationArray, sourceArray, sourceArray.length);

        System.out.println(new String(destinationArray));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}