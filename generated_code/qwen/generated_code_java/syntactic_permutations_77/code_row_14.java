import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        int memorySize = 256; // Example size for memory block
        ByteBuffer memoryBlock = allocateMemory(memorySize);

        Person john = new Person();
        john.setStatus(0);
        setName(john, "John", memoryBlock);

        System.out.println("Person Name: " + getName(john, memoryBlock));
        System.out.println("Person Status: " + john.getStatus());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }

    public static void setName(Person person, String name, ByteBuffer memoryBlock) {
        int nameOffset = Integer.BYTES; // Assuming status is stored first
        CharBuffer charBuffer = StandardCharsets.UTF_8.encode(name);
        byte[] nameBytes = new byte[charBuffer.remaining()];
        charBuffer.get(nameBytes);
        memoryBlock.position(nameOffset).put(nameBytes);
    }

    public static String getName(Person person, ByteBuffer memoryBlock) {
        int nameOffset = Integer.BYTES; // Assuming status is stored first
        memoryBlock.position(nameOffset);
        StringBuilder nameBuilder = new StringBuilder();
        byte b;
        while (memoryBlock.hasRemaining() && (b = memoryBlock.get()) != 0) { // Null-terminated string
            nameBuilder.append((char) b);
        }
        return nameBuilder.toString();
    }

    static class Person {
        private int status;

        public void setStatus(int status) {
            this.status = status;
        }

        public int getStatus() {
            return status;
        }
    }
}