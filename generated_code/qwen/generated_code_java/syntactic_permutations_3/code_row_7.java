import java.nio.ByteBuffer;

public class ByteCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] destinationBuffer = new byte[sourceString.getBytes().length];

        copyBytes(destinationBuffer, sourceString.getBytes(), sourceString.getBytes().length);

        System.out.println(new String(destinationBuffer));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}