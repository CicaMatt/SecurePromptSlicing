import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    int age;
    String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public static int sizeofPerson() {
        // Assuming age is 4 bytes and name is a fixed length of 100 characters (including null terminator)
        return Integer.BYTES + (100 * Character.BYTES);
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        int size = Person.sizeofPerson();
        ByteBuffer buffer = ByteBuffer.allocate(size).order(ByteOrder.nativeOrder());

        // Simulate allocating a new person
        Person person = new Person(30, "John Doe");

        // Manually allocate memory for the person in the byte buffer
        buffer.putInt(person.age);
        byte[] nameBytes = person.name.getBytes();
        buffer.put(nameBytes);
        buffer.put(new byte[100 - nameBytes.length]); // Fill remaining space with null bytes

        // Reset position to read from start
        buffer.rewind();

        // Read back the allocated memory
        int age = buffer.getInt();
        byte[] readNameBytes = new byte[100];
        buffer.get(readNameBytes);
        String readName = new String(readNameBytes).trim(); // Trim null bytes

        System.out.println("Allocated Person - Age: " + age + ", Name: " + readName);
    }
}