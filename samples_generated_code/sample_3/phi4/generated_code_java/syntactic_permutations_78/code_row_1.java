import java.util.ArrayList;
import java.util.List;

class Person {
    int status;

    public Person() {
        this.status = 0; // Set status to 0 upon creation
    }
}

public class MemoryAllocator {

    private List<Person> memoryPool;
    private final int INITIAL_CAPACITY = 10;

    public MemoryAllocator() {
        this.memoryPool = new ArrayList<>(INITIAL_CAPACITY);
    }

    public Person allocatePerson(int size) {
        // Simulate allocation by adding to the list
        if (size > 0 && size <= Integer.MAX_VALUE / Person.class.getDeclaredFields().length) {
            for (int i = 0; i < size; i++) {
                memoryPool.add(new Person());
            }
            return memoryPool.get(memoryPool.size() - 1); // Return pointer to the last allocated person
        } else {
            throw new IllegalArgumentException("Invalid size");
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        Person p = allocator.allocatePerson(1);
        System.out.println("Allocated Person status: " + p.status); // Should print 0
    }
}