class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    private static final int POOL_SIZE = 100; // Example pool size

    private static Person[] memoryPool = new Person[POOL_SIZE];
    private static int nextIndex = 0;

    public static synchronized Person allocatePerson() {
        if (nextIndex < POOL_SIZE) {
            memoryPool[nextIndex] = new Person();
            return memoryPool[nextIndex++];
        } else {
            throw new OutOfMemoryError("No more space in the memory pool");
        }
    }

    public static void main(String[] args) {
        try {
            for (int i = 0; i < POOL_SIZE + 10; i++) { // Attempt to allocate more than the pool size
                Person p = MemoryAllocator.allocatePerson();
                System.out.println("Allocated person with status: " + p.status);
            }
        } catch (OutOfMemoryError e) {
            System.err.println(e.getMessage());
        }
    }
}