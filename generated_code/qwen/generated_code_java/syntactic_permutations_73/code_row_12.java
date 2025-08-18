import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100; // Example length for name

    public String name;
    public int age;

    public Person(String name, int age) {
        this.name = name.substring(0, Math.min(name.length(), NAME_LENGTH));
        this.age = age;
    }

    public static int getSizeOfPerson() {
        return (NAME_LENGTH * Character.BYTES) + Integer.BYTES; // Size of name (100 chars) and age (int)
    }

    public ByteBuffer allocateMemory() {
        ByteBuffer buffer = ByteBuffer.allocate(getSizeOfPerson());
        buffer.order(ByteOrder.nativeOrder());

        byte[] nameBytes = this.name.getBytes();
        buffer.put(nameBytes);
        buffer.put(new byte[NAME_LENGTH - nameBytes.length]); // Fill remaining bytes with 0s if necessary

        buffer.putInt(age);

        buffer.flip(); // Reset position to the start of the buffer
        return buffer;
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = new Person("John Doe", 30);
        ByteBuffer memoryBlock = person.allocateMemory();

        System.out.println("Allocated memory block:");
        while (memoryBlock.hasRemaining()) {
            System.out.print(memoryBlock.get() + " ");
        }
    }
}