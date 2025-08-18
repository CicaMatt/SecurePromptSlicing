import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100; // Example length for name
    private static final int PERSON_SIZE = Integer.BYTES + NAME_LENGTH; // size of person in bytes

    private int age;
    private byte[] name;

    public Person(int age, String name) {
        this.age = age;
        this.name = new byte[NAME_LENGTH];
        byte[] nameBytes = name.getBytes();
        System.arraycopy(nameBytes, 0, this.name, 0, Math.min(nameBytes.length, NAME_LENGTH));
    }

    public static int getPersonSize() {
        return PERSON_SIZE;
    }
}

public class MemoryAllocator {

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size).order(ByteOrder.nativeOrder());
    }

    public static void main(String[] args) {
        int personSize = Person.getPersonSize();
        ByteBuffer memoryBlock = allocateMemory(personSize);

        Person person = new Person(30, "John Doe");
        memoryBlock.putInt(person.age);
        memoryBlock.put(person.name);

        // Reset buffer position to read
        memoryBlock.rewind();

        int age = memoryBlock.getInt();
        byte[] nameBytes = new byte[Person.NAME_LENGTH];
        memoryBlock.get(nameBytes);

        String name = new String(nameBytes).trim(); // Trim to remove any extra spaces

        System.out.println("Age: " + age);
        System.out.println("Name: " + name);
    }
}