import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100; // Example length for name
    private static final int PERSON_SIZE = NAME_LENGTH * Character.BYTES + Integer.BYTES + Float.BYTES;

    private String name;
    private int age;
    private float height;

    public Person(String name, int age, float height) {
        this.name = name;
        this.age = age;
        this.height = height;
    }

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocate(PERSON_SIZE).order(ByteOrder.nativeOrder());
    }

    public void writeDataToBuffer(ByteBuffer buffer) {
        byte[] nameBytes = name.getBytes();
        if (nameBytes.length > NAME_LENGTH) {
            throw new IllegalArgumentException("Name is too long");
        }
        buffer.put(nameBytes);
        for (int i = nameBytes.length; i < NAME_LENGTH; i++) {
            buffer.put((byte) 0); // Fill remaining space with null bytes
        }
        buffer.putInt(age);
        buffer.putFloat(height);
    }

    public static Person readDataFromBuffer(ByteBuffer buffer) {
        byte[] nameBytes = new byte[NAME_LENGTH];
        buffer.get(nameBytes);
        String name = new String(nameBytes).trim();
        int age = buffer.getInt();
        float height = buffer.getFloat();
        return new Person(name, age, height);
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person("John Doe", 30, 5.9f);
        ByteBuffer buffer = Person.allocatePerson();
        person.writeDataToBuffer(buffer);

        buffer.rewind(); // Rewind to the beginning of the buffer for reading
        Person readPerson = Person.readDataFromBuffer(buffer);
        System.out.println("Name: " + readPerson.name);
        System.out.println("Age: " + readPerson.age);
        System.out.println("Height: " + readPerson.height);
    }
}