public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024;
    private byte[] memoryPool = new byte[MEMORY_SIZE];
    private boolean[] used = new boolean[MEMORY_SIZE];

    public long alloc(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            if (isFree(i, size)) {
                markUsed(i, size);
                return i;
            }
        }
        throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes");
    }

    private boolean isFree(int start, int size) {
        for (int i = start; i < start + size; i++) {
            if (used[i]) {
                return false;
            }
        }
        return true;
    }

    private void markUsed(int start, int size) {
        for (int i = start; i < start + size; i++) {
            used[i] = true;
        }
    }

    public static class Person {
        int status;
        String name;

        public Person() {
            this.status = 0;
            this.name = "";
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        int personSize = Integer.BYTES * 2 + " ".length(); // Assuming status and name are stored in memory

        long address = allocator.alloc(personSize);
        System.out.println("Allocated at address: " + address);

        Person person = new Person();
        System.out.println("Person created with status: " + person.status + " and name: '" + person.name + "'");
    }
}