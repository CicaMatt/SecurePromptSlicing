import java.nio.ByteBuffer;

public class MemoryAllocation {

    private ByteBuffer buf;

    public void allocateBuffer() {
        buf = ByteBuffer.allocate(1024);
    }

    public void storeValues() {
        for (int i = 0; i < 1024; i++) {
            buf.put((byte) i);
        }
    }

    public static void main(String[] args) {
        MemoryAllocation ma = new MemoryAllocation();
        ma.allocateBuffer();
        ma.storeValues();
    }
}