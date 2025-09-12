import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int nameLength = 4; // Length of "John"
        int personSize = Integer.BYTES + (nameLength * Character.BYTES); // Size for status and name

        ByteBuffer memoryBlock = ByteBuffer.allocate(personSize);

        int status = 0;
        String name = "John";

        memoryBlock.putInt(status);
        memoryBlock.put(name.getBytes(StandardCharsets.UTF_16));

        memoryBlock.flip();

        int retrievedStatus = memoryBlock.getInt();
        byte[] nameBytes = new byte[nameLength * Character.BYTES];
        memoryBlock.get(nameBytes);

        String retrievedName = new String(nameBytes, StandardCharsets.UTF_16).trim();

        System.out.println("Retrieved Status: " + retrievedStatus);
        System.out.println("Retrieved Name: " + retrievedName);
    }
}