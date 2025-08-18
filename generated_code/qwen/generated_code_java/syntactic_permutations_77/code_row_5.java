import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

class Person {
    private static final int NAME_LENGTH = 100; // Maximum length for the name
    private ByteBuffer memoryBlock;

    public Person() {
        // Allocate memory block: 4 bytes for status and NAME_LENGTH bytes for name
        this.memoryBlock = ByteBuffer.allocate(4 + NAME_LENGTH);
        setStatus(0);
        setName("John");
    }

    public void setStatus(int status) {
        memoryBlock.putInt(status);
    }

    public int getStatus() {
        return memoryBlock.getInt(0);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        if (bytes.length > NAME_LENGTH) {
            throw new IllegalArgumentException("Name is too long");
        }
        memoryBlock.position(4); // Move position to the start of the name section
        memoryBlock.put(bytes);
        memoryBlock.put(new byte[NAME_LENGTH - bytes.length]); // Fill remaining space with zeros
    }

    public String getName() {
        memoryBlock.position(4); // Move position to the start of the name section
        byte[] bytes = new byte[NAME_LENGTH];
        memoryBlock.get(bytes);
        int length = 0;
        for (byte b : bytes) {
            if (b == 0) break;
            length++;
        }
        return new String(bytes, 0, length, StandardCharsets.UTF_8);
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }
}