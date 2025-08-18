import java.util.ArrayList;
import java.util.List;

class Person {
    int id;
    int status; // 0 indicates default status

    public Person(int id) {
        this.id = id;
        this.status = 0; // setting status to 0 when a new person is allocated
    }

    @Override
    public String toString() {
        return "Person{id=" + id + ", status=" + status + '}';
    }
}

public class MemoryAllocator {

    private List<Person> memoryPool;

    public MemoryAllocator() {
        this.memoryPool = new ArrayList<>();
    }

    // Method to allocate a block of memory and return a pointer (reference) to the beginning
    public Person[] allocateMemory(int size) {
        if (size <= 0) {
            throw new IllegalArgumentException("Size must be greater than zero.");
        }
        
        Person[] allocatedBlock = new Person[size];
        for (int i = 0; i < size; i++) {
            // Simulate a person allocation with a unique ID and default status
            Person newPerson = new Person(i + 1);
            memoryPool.add(newPerson); // Track the allocated persons if needed
            allocatedBlock[i] = newPerson;
        }
        
        return allocatedBlock;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        int size = 5; // Example size for allocation
        Person[] block = allocator.allocateMemory(size);
        
        for (Person person : block) {
            System.out.println(person);
        }
    }
}