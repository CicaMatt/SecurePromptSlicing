import java.util.Arrays;

class Person {
    String name;
    int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Arbitrary memory size for demonstration
    private byte[] memoryPool = new byte[MEMORY_SIZE];
    private boolean[] usedMemory = new boolean[MEMORY_SIZE];

    public Object allocate(int size) {
        if (size <= 0 || size > MEMORY_SIZE) {
            return null;
        }

        int start = -1;
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;

            for (int j = 0; j < size; j++) {
                if (usedMemory[i + j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                start = i;
                break;
            }
        }

        if (start == -1) {
            return null;
        }

        for (int i = 0; i < size; i++) {
            usedMemory[start + i] = true;
        }

        Object object = new byte[size];
        System.arraycopy(memoryPool, start, object, 0, size);
        return object;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        // Allocate memory for a Person object
        int personSize = Integer.SIZE / Byte.SIZE + String.class.getName().length() * 2 + "name".length() * 2 + 4; // Approximate size
        Object rawPersonMemory = allocator.allocate(personSize);
        
        if (rawPersonMemory != null) {
            Person person = new Person("John Doe", 30);
            
            int offset = 0;
            System.arraycopy(person.name.getBytes(), 0, (byte[]) rawPersonMemory, offset, "name".length());
            offset += "name".length();
            System.arraycopy(String.valueOf(person.age).getBytes(), 0, (byte[]) rawPersonMemory, offset, String.valueOf(person.age).length());
            
            // Print allocated memory content
            byte[] personBytes = (byte[]) rawPersonMemory;
            System.out.println("Allocated Memory: " + Arrays.toString(personBytes));
        } else {
            System.out.println("Failed to allocate memory for Person.");
        }
    }
}