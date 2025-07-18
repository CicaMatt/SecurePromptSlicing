import java.nio.*;

public class ChunkCopy {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(5);
        buffer1.put((byte) 0xCA).put((byte) 0xFE).put((byte) 0xBA).put((byte) 0xBE).flip();

        ByteBuffer buffer2 = ByteBuffer.allocateDirect(buffer1.limit());
        while (buffer1.hasRemaining()) {
            buffer2.put(buffer1);
        }
        System.out.println(buffer2.array().toString());
    }
}