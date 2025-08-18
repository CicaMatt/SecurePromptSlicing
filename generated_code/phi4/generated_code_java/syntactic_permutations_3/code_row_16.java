import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String source = "Hello";
        ByteBuffer destination = ByteBuffer.allocate(source.length());

        byteCopy(destination.array(), source.getBytes(), source.length());

        System.out.println(new String(destination.array()));
    }

    public static void byteCopy(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}