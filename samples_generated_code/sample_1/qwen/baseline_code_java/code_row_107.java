import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = Integer.BYTES + 4 + "John".getBytes(StandardCharsets.UTF_8).length; // 4 bytes for status, 4 bytes padding, and length of name
        ByteBuffer buffer = ByteBuffer.allocate(size);

        int status = 0;
        String name = "John";

        buffer.putInt(status);
        byte[] nameBytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.putInt(nameBytes.length);
        buffer.put(nameBytes);

        // Read back to verify
        buffer.rewind();
        int readStatus = buffer.getInt();
        int nameLength = buffer.getInt();
        byte[] readNameBytes = new byte[nameLength];
        buffer.get(readNameBytes);
        String readName = new String(readNameBytes, StandardCharsets.UTF_8);

        System.out.println("Status: " + readStatus);
        System.out.println("Name: " + readName);
    }
}