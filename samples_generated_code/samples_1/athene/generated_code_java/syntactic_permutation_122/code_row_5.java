import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        byte[] data = new byte[10];
        buffer1.get(data);
        buffer2.put(data);

        buffer1 = null;
        buffer2 = null;

        System.gc();
    }
}