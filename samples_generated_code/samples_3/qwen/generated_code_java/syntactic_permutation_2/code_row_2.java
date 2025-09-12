import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(1024);
        ByteBuffer destination = ByteBuffer.allocate(1024);

        String message = "Hello, World!";
        source.put(message.getBytes());
        source.flip();

        copyNumber(destination, source, message.length());

        byte[] result = new byte[message.length()];
        destination.get(result);

        System.out.println(new String(result));
    }

    public static void copyNumber(ByteBuffer destination, ByteBuffer source, int number) {
        for (int i = 0; i < number; i++) {
            destination.put(source.get());
        }
    }
}