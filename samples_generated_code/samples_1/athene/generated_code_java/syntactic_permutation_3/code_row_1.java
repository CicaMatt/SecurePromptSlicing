import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void memcpy(byte[] dest, byte[] src, int num) {
        System.arraycopy(src, 0, dest, 0, num);
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        byte[] source = "Hello".getBytes();

        memcpy(buffer, source, 5);

        System.out.println(new String(buffer, 0, 5));
    }
}