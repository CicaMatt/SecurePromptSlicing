public class MemoryAllocator {

    private static final int SIZE = 1024; // Size of memory pool
    private byte[] memoryPool = new byte[SIZE];
    private boolean[] used = new boolean[SIZE];

    public int allocate(int size) {
        for (int i = 0, count = 0; i < SIZE; i++) {
            if (!used[i]) {
                if (++count == size) {
                    for (int j = i - size + 1; j <= i; j++) {
                        used[j] = true;
                    }
                    return i - size + 1;
                }
            } else {
                count = 0;
            }
        }
        throw new RuntimeException("Out of memory");
    }

    public void deallocate(int address, int size) {
        for (int i = address; i < address + size; i++) {
            used[i] = false;
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person() {
            this.status = 0;
            this.name = "John";
        }

        @Override
        public String toString() {
            return "Person{name='" + name + "', status=" + status + '}';
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        // Assume size of Person object is 1 for simplicity in this example
        int address = allocator.allocate(1);
        Person person = new Person();

        System.out.println(person);

        allocator.deallocate(address, 1);
    }
}