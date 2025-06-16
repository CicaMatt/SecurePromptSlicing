import java.nio.*;

public class Main {
    public static void main(String[] args) {
        ByteBuffer buf1 = ByteBuffer.allocate(4);
        ByteBuffer buf2 = ByteBuffer.allocate(4);

        // write data to first buffer
        byte[] array = { 0, 1, 2, 3 };
        buf1.put(array);

        // read from the first and write to the second
        for (int i = 0; i < array.length; i++) {
            byte b = buf1.get();
            buf2.put(b);
        }

        // print out the second buffer
        buf2.flip();
        while (buf2.hasRemaining()) {
            System.out.println(buf2.get());
        }
    }
}