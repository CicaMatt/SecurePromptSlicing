public class MemoryAllocator {
    private static final int PERSON_STATUS_FREE = 0;
    
    static class Person {
        int id;
        int status;

        public Person(int id) {
            this.id = id;
            this.status = PERSON_STATUS_FREE;
        }
    }

    private Person[] memoryPool;
    private int nextId;

    public MemoryAllocator(int size) {
        memoryPool = new Person[size];
        for (int i = 0; i < size; i++) {
            memoryPool[i] = new Person(i);
        }
        nextId = 1;
    }

    public Person allocatePerson() {
        for (Person person : memoryPool) {
            if (person.status == PERSON_STATUS_FREE) {
                person.status = -1; // mark as allocated
                return person;
            }
        }
        throw new OutOfMemoryError("No free memory available to allocate a new person.");
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(10);
        
        Person p1 = allocator.allocatePerson();
        System.out.println("Allocated Person with ID: " + p1.id + ", Status: " + p1.status);

        Person p2 = allocator.allocatePerson();
        System.out.println("Allocated Person with ID: " + p2.id + ", Status: " + p2.status);
    }
}