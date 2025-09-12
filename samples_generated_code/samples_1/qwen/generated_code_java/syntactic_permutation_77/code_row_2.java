import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = 1024; // Example size for memory allocation
        ByteBuffer buffer = allocateMemory(size);

        Person john = new Person();
        john.setName("John");
        storePersonInMemory(buffer, john);

        System.out.println(retrieveNameFromMemory(buffer));
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }

    public static void storePersonInMemory(ByteBuffer buffer, Person person) {
        byte[] nameBytes = person.getName().getBytes(StandardCharsets.UTF_8);
        buffer.putInt(nameBytes.length); // Store length of the name
        buffer.put(nameBytes); // Store the name
    }

    public static String retrieveNameFromMemory(ByteBuffer buffer) {
        buffer.rewind(); // Reset buffer position to start
        int nameLength = buffer.getInt();
        byte[] nameBytes = new byte[nameLength];
        buffer.get(nameBytes);
        return new String(nameBytes, StandardCharsets.UTF_8);
    }
}

class Person {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}