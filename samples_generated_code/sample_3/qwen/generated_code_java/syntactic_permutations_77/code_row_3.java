import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocation {
    public static void main(String[] args) {
        int memorySize = 128; // Example size for demonstration
        ByteBuffer buffer = ByteBuffer.allocate(memorySize);

        Person person = new Person();
        person.setStatus(0);
        person.setName("");

        allocateMemory(person, buffer);
    }

    private static void allocateMemory(Person person, ByteBuffer buffer) {
        buffer.putInt(person.getStatus());
        byte[] nameBytes = person.getName().getBytes(StandardCharsets.UTF_8);
        buffer.put(nameBytes);
        for (int i = nameBytes.length; i < 64; i++) { // Assuming name is stored in a fixed size of 64 bytes
            buffer.put((byte) 0); // Fill remaining bytes with null terminator or padding
        }
    }
}

class Person {
    private int status;
    private String name;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}