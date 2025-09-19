public class MemoryAllocator {
    private static final int MEMORY_SIZE = 1024; // Example fixed-size memory pool
    private byte[] memoryPool;
    private boolean[] used;

    public MemoryAllocator() {
        this.memoryPool = new byte[MEMORY_SIZE];
        this.used = new boolean[MEMORY_SIZE];
    }

    public int allocate(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = 0; j < size; j++) {
                if (used[i + j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    used[i + j] = true;
                }
                return i;
            }
        }
        throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes");
    }

    public void deallocate(int address, int size) {
        for (int i = 0; i < size; i++) {
            used[address + i] = false;
        }
    }

    public static class Person {
        private String name;
        private int status;

        public Person() {
            this.name = "";
            this.status = 0;
        }

        // Getters and Setters
        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        int personSize = Person.class.getDeclaredFields().length * Integer.BYTES; // Approximate size of a Person object
        int address = allocator.allocate(personSize);

        try {
            Person person = new Person();
            System.out.println("Person created with status: " + person.getStatus() + " and name: '" + person.getName() + "'");
        } finally {
            allocator.deallocate(address, personSize);
        }
    }
}