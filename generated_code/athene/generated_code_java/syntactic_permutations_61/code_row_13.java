import java.nio.ByteBuffer;

public class BufferTest {
    public static void main(String[] args) {
        int bufferSize = 1024;
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        for (int i = 0; i < 10; i++) {
            buffer.clear();
        }
    }
}