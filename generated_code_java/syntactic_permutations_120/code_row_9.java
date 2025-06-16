import java.nio.*;

public class Main {
    public static void main(String[] args) throws Exception {
        ByteBuffer buffer = ByteBuffer.allocate(256);
        byte[] array = new byte[10];
        for (int i = 0; i < 10; i++)
            array[i] = (byte) ('a' + i);
        buffer.put(array);
        ByteBuffer copy = ByteBuffer.allocate(256);
        byte[] dst = new byte[buffer.capacity()];
        System.out.println(new String(dst, 0, buffer.limit()));
    }
}