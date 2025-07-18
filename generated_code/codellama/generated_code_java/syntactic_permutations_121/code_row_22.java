import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(256);
        byte[] data = new byte[10];
        for (int i = 0; i < data.length; i++) {
            data[i] = (byte) i;
        }
        buffer.put(data);
        System.out.println(buffer.get());
        ByteBuffer duplicate = buffer.duplicate();
        System.out.println(duplicate.get());
        buffer.clear();
        System.out.println(duplicate.get());
        duplicate.clear();
    }
}