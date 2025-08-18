import java.nio.ByteBuffer;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;
    private ByteBuffer buf;

    public void allocateBuffer() {
        this.buf = ByteBuffer.allocate(BUFFER_SIZE);
    }

    public void readAndStore(byte[] data) {
        if (data.length > BUFFER_SIZE) {
            throw new IllegalArgumentException("Data exceeds buffer size");
        }
        buf.clear();
        buf.put(data);
    }

    public static void main(String[] args) {
        BufferExample example = new BufferExample();
        example.allocateBuffer();
        byte[] testData = new byte[BUFFER_SIZE];
        for (int i = 0; i < BUFFER_SIZE; i++) {
            testData[i] = (byte) i;
        }
        example.readAndStore(testData);
    }
}