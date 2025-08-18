import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        ByteBuffer destination = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            source.put((byte)i);
        }

        destination.put(source.array());

        System.out.println(new String(destination.array()));
    }
}