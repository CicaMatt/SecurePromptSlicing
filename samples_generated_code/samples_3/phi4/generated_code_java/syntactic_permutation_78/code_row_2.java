import java.util.ArrayList;
import java.util.List;

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + '}';
    }
}

public class MemoryAllocator {

    private List<byte[]> memoryPool = new ArrayList<>();
    private int allocationSize;

    public MemoryAllocator(int blockSize) {
        this.allocationSize = blockSize;
    }

    public byte[] allocate() {
        byte[] block = new byte[allocationSize];
        memoryPool.add(block);
        return block;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);

        // Allocate memory for a new Person object
        byte[] personMemory = allocator.allocate();

        // Simulate storing a Person in the allocated memory (for demonstration purposes)
        int nameOffset = 0;
        int ageOffset = 50; // Assuming String length of "John Doe" + null terminator

        String name = "John Doe";
        int age = 30;

        System.arraycopy(name.getBytes(), 0, personMemory, nameOffset, name.length() + 1);
        for (int i = 0; i < age / 10; i++) {
            personMemory[ageOffset + i] = (byte) ('0' + (age % 10));
            age /= 10;
        }

        // Create a Person object from the allocated memory
        String extractedName = new String(personMemory, nameOffset).trim();
        int extractedAge = Integer.parseInt(new String(personMemory, ageOffset));

        Person person = new Person(extractedName, extractedAge);

        System.out.println(person);
    }
}