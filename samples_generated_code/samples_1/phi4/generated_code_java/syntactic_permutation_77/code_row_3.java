import java.util.Arrays;

public class MemoryAllocator {
    private static final int MEMORY_SIZE = 1024;
    private byte[] memory = new byte[MEMORY_SIZE];
    private boolean[] allocated = new boolean[MEMORY_SIZE];

    public MemoryAllocator() {
        Arrays.fill(allocated, false);
    }

    public long allocate(int size) {
        if (size <= 0 || size > MEMORY_SIZE) return -1;

        int freeCount = 0;
        for (int i = 0; i < MEMORY_SIZE; i++) {
            if (!allocated[i]) {
                freeCount++;
                if (freeCount == size) {
                    for (int j = i - size + 1; j <= i; j++) {
                        allocated[j] = true;
                    }
                    return i - size + 1;
                }
            } else {
                freeCount = 0;
            }
        }
        return -1;
    }

    public void deallocate(long address, int size) {
        if (address < 0 || address >= MEMORY_SIZE || size <= 0) return;

        for (int i = (int) address; i < address + size; i++) {
            allocated[i] = false;
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person() {
            this.status = 0;
            this.name = "";
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        long personAddress = allocator.allocate(Person.class.getDeclaredFields().length + 1); // Allocate space for Person object
        if (personAddress != -1) {
            System.out.println("Person allocated at address: " + personAddress);
            Person person = new Person(); // Create a new person and set status to 0, name to ""
            System.out.println("Person Status: " + person.getStatus() + ", Name: " + person.getName());
        } else {
            System.out.println("Memory allocation failed.");
        }
    }
}