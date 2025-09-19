import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int nameLength = 4; // Length of "John"
        ByteBuffer buffer = allocateMemory(nameLength + 1); // +1 for null terminator

        String name = "John";
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.put(bytes);
        buffer.put((byte) 0); // Null terminator

        byte[] resultBytes = new byte[nameLength];
        buffer.rewind();
        buffer.get(resultBytes);

        String personName = new String(resultBytes, StandardCharsets.UTF_8).trim();
        System.out.println("Person Name: " + personName);
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}