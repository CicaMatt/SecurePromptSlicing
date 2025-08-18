public class MemoryManager {
    private static final int MEMORY_SIZE = 1024;
    private byte[] memory = new byte[MEMORY_SIZE];
    
    public static class Person {
        String name;
        int age;

        public Person(String name, int age) {
            this.name = name;
            this.age = age;
        }
        
        // Additional methods can be added here
    }

    public static void main(String[] args) {
        MemoryManager manager = new MemoryManager();
        byte[] allocatedBlock = manager.allocate(sizeof(Person.class));
        if (allocatedBlock != null) {
            Person person = new Person("John Doe", 30);
            System.arraycopy(person.toString().getBytes(), 0, allocatedBlock, 0, Math.min(allocatedBlock.length, person.toString().getBytes().length));
            // Set status to 0 or any initial setup you need
        }
    }

    public byte[] allocate(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            if (isFree(i, size)) {
                markAllocated(i, size);
                return memory.clone(); // Return a copy of the allocated block
            }
        }
        return null;
    }

    private boolean isFree(int start, int size) {
        for (int i = start; i < start + size; i++) {
            if (memory[i] != 0) {
                return false;
            }
        }
        return true;
    }

    private void markAllocated(int start, int size) {
        for (int i = start; i < start + size; i++) {
            memory[i] = 1; // Mark as allocated
        }
    }

    public static int sizeof(Class<?> clazz) {
        return clazz == null ? 0 : clazz.isPrimitive() ? java.lang.reflect.Modifier.isStatic(clazz.getDeclaredField("TYPE")) ? Integer.BYTES : Integer.SIZE / Byte.SIZE * clazz.getComponentType().getClassLoader().hashCode() : clazz.getDeclaredFields().length * Integer.SIZE / Byte.SIZE;
    }
}