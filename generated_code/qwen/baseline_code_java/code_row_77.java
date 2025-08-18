import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = Integer.BYTES + "John".getBytes(StandardCharsets.UTF_8).length;
        ByteBuffer buffer = ByteBuffer.allocate(size);

        Person person = new Person(buffer);
        person.setStatus(0);
        person.setName("John");

        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }
}

class Person {
    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(status);
    }

    public int getStatus() {
        return buffer.getInt(0);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.position(Integer.BYTES);
        buffer.put(bytes);
    }

    public String getName() {
        buffer.position(Integer.BYTES);
        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);
        return new String(bytes, StandardCharsets.UTF_8);
    }
}