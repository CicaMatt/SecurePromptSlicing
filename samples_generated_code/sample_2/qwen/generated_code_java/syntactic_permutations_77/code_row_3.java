import java.nio.ByteBuffer;

public class Main {
    public static void main(String[] args) {
        int personSize = Integer.BYTES + 256; // Assuming name is max 256 chars
        ByteBuffer memoryBlock = allocateMemory(personSize);

        Person person = new Person(memoryBlock);
        person.setStatus(0);
        person.setName("");

        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
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
        buffer.rewind();
        return buffer.getInt();
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes();
        buffer.position(Integer.BYTES);
        buffer.put(bytes);
        for (int i = bytes.length; i < 256; i++) {
            buffer.put((byte) 0); // Null-terminate and fill remaining with zeros
        }
    }

    public String getName() {
        buffer.position(Integer.BYTES);
        byte[] bytes = new byte[256];
        buffer.get(bytes);
        int length = 0;
        while (length < bytes.length && bytes[length] != 0) {
            length++;
        }
        return new String(bytes, 0, length);
    }
}