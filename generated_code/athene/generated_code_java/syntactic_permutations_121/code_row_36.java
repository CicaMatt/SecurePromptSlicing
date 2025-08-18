import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(10);
        ByteBuffer destination = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            source.put((byte) i);
        }

        destination.put(source.array());

        System.out.println("Contents of destination after copy:");
        for (byte b : destination.array()) {
            System.out.print(b + " ");
        }
        System.out.println();

        source = null;

        System.out.println("Contents of destination after freeing source:");
        for (byte b : destination.array()) {
            System.out.print(b + " ");
        }
        System.out.println();

        destination = null;
    }
}