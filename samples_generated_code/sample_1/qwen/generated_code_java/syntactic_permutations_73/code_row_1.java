import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePersonMemory();
        System.out.println("Allocated memory address: " + System.identityHashCode(person));
    }

    public static Person allocatePersonMemory() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.SIZE);
        return new Person(buffer);
    }
}

class Person {
    public static final int SIZE = 16; // Assuming a simple structure with fixed size for demonstration

    private final ByteBuffer memory;

    public Person(ByteBuffer memory) {
        this.memory = memory;
    }

    // Example getters and setters
    public void setName(String name) {
        byte[] bytes = name.getBytes();
        if (bytes.length > 8) throw new IllegalArgumentException("Name is too long");
        memory.position(0).put(bytes);
    }

    public String getName() {
        byte[] bytes = new byte[8];
        memory.position(0).get(bytes);
        return new String(bytes).trim();
    }

    public void setAge(int age) {
        memory.position(8).putInt(age);
    }

    public int getAge() {
        return memory.position(8).getInt();
    }
}