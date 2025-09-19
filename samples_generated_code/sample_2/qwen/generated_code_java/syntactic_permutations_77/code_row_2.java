import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocation {
    public static void main(String[] args) {
        int nameSize = 5; // Size for "John" + null terminator
        ByteBuffer buffer = ByteBuffer.allocate(nameSize);
        
        String name = "John";
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.put(bytes);
        buffer.put((byte) 0); // Null terminator

        byte[] personName = new byte[nameSize];
        buffer.rewind();
        buffer.get(personName);

        System.out.println(new String(personName, StandardCharsets.UTF_8).trim());
    }
}