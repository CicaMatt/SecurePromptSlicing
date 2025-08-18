import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) 'A');
        }

        buffer.rewind();

        while (buffer.hasRemaining()) {
            System.out.print((char) buffer.get());
        }
    }
}