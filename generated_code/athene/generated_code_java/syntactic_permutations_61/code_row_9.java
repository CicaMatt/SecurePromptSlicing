import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        ByteBuffer buffer;
        while (true) {
            buffer = ByteBuffer.allocate(1024);
            buffer.clear();
        }
    }
}