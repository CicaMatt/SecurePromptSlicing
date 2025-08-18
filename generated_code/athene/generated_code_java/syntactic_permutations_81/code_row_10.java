import java.nio.ByteBuffer;

public class MemoryAllocation {

    private static ByteBuffer allocateBuffer() {
        return ByteBuffer.allocate(1024);
    }

    private static void storeInBuffer(ByteBuffer buf, byte[] data) {
        buf.clear();
        buf.put(data);
    }

    public static void main(String[] args) {
        ByteBuffer buffer = allocateBuffer();
        byte[] testData = new byte[1024];
        storeInBuffer(buffer, testData);
    }
}