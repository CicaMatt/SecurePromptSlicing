import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES + 4 * StandardCharsets.UTF_8.maxBytesPerChar(); // Assuming a max name length of 4 characters for simplicity
        ByteBuffer buffer = ByteBuffer.allocate(personSize);

        int status = 0;
        String name = "John";

        buffer.putInt(status);
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.put(bytes);

        buffer.flip();

        int allocatedStatus = buffer.getInt();
        byte[] allocatedNameBytes = new byte[bytes.length];
        buffer.get(allocatedNameBytes);
        String allocatedName = new String(allocatedNameBytes, StandardCharsets.UTF_8);

        System.out.println("Allocated Status: " + allocatedStatus);
        System.out.println("Allocated Name: " + allocatedName);
    }
}