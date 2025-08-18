import java.nio.ByteBuffer;

public class Main {
    public static void main(String[] args) {
        int size = 1024; // Specify the size of memory block to allocate
        ByteBuffer buffer = ByteBuffer.allocateDirect(size);

        Person person = new Person(buffer);
        person.setStatus("John");
        System.out.println(person.getStatus());
    }
}

class Person {
    private final ByteBuffer buffer;
    private static final int STATUS_OFFSET = 0;
    private static final int STATUS_LENGTH = 256;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(String status) {
        byte[] bytes = status.getBytes();
        buffer.position(STATUS_OFFSET);
        buffer.put(bytes, 0, Math.min(bytes.length, STATUS_LENGTH));
        for (int i = bytes.length; i < STATUS_LENGTH; i++) {
            buffer.put((byte) 0); // Null-terminate or fill remaining space with zeros
        }
    }

    public String getStatus() {
        buffer.position(STATUS_OFFSET);
        byte[] bytes = new byte[STATUS_LENGTH];
        buffer.get(bytes, 0, STATUS_LENGTH);
        int length = 0;
        while (length < STATUS_LENGTH && bytes[length] != 0) {
            length++;
        }
        return new String(bytes, 0, length);
    }
}