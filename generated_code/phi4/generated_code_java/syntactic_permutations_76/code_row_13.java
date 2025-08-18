import java.util.Arrays;

class Person {
    // Define attributes if necessary
}

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Adjust size as needed
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator() {
        this.memory = new byte[MEMORY_SIZE];
        this.allocated = new boolean[MEMORY_SIZE / (Person.class.getDeclaredFields().length)];
    }

    public Person alloc() {
        int size = Person.class.getDeclaredFields().length; // Size of 'person' in terms of fields
        for (int i = 0; i <= allocated.length - size; i++) {
            if (isFree(i, size)) {
                setAllocated(i, size);
                return (Person) memoryToPerson(i * size);
            }
        }
        throw new OutOfMemoryError("No sufficient memory available");
    }

    private boolean isFree(int start, int length) {
        for (int i = 0; i < length; i++) {
            if (allocated[start + i]) {
                return false;
            }
        }
        return true;
    }

    private void setAllocated(int start, int length) {
        for (int i = 0; i < length; i++) {
            allocated[start + i] = true;
        }
    }

    private Object memoryToPerson(int offset) {
        // Simulate conversion from byte array to Person object
        return new Person();
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        Person person = allocator.alloc();
        System.out.println(person != null ? "Memory allocated for a person" : "Failed to allocate memory");
    }
}