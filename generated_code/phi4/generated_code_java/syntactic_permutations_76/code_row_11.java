public class Person {
    private int status;
    public static final int SIZE = Integer.BYTES; // Assuming sizeof(int) is required

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

class MemoryAllocator {
    private byte[] memoryPool;
    private int pointer;

    public MemoryAllocator(int size) {
        memoryPool = new byte[size];
        pointer = 0;
    }

    public Person allocatePerson() {
        if (pointer + Person.SIZE > memoryPool.length) {
            throw new OutOfMemoryError("Not enough memory to allocate a new person");
        }
        
        int startAddress = pointer;
        pointer += Person.SIZE;

        return readPersonFromMemory(startAddress);
    }

    private Person readPersonFromMemory(int address) {
        byte[] personBytes = new byte[Person.SIZE];
        System.arraycopy(memoryPool, address, personBytes, 0, Person.SIZE);

        // Assuming the status is stored in the first int bytes
        int offset = Integer.BYTES;
        int status = ((personBytes[offset] & 0xFF) << 24)
                    | ((personBytes[offset + 1] & 0xFF) << 16)
                    | ((personBytes[offset + 2] & 0xFF) << 8)
                    | (personBytes[offset + 3] & 0xFF);

        Person person = new Person();
        person.setStatus(status);
        return person;
    }

    public void deallocatePerson(Person person, int address) {
        // Reset the status to 0
        byte[] personBytes = new byte[Person.SIZE];
        System.arraycopy(memoryPool, address, personBytes, 0, Person.SIZE);

        // Assuming the status is stored in the first int bytes
        int offset = Integer.BYTES;
        for (int i = 0; i < Integer.BYTES; i++) {
            personBytes[offset + i] = 0;
        }

        System.arraycopy(personBytes, 0, memoryPool, address, Person.SIZE);
    }
}

public class Main {
    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024); // Initialize with a pool size of 1024 bytes

        Person person1 = allocator.allocatePerson();
        System.out.println("Allocated person with status: " + person1.getStatus());

        int address1 = 0; // Assuming we know the starting address
        allocator.deallocatePerson(person1, address1);
        
        Person person2 = allocator.allocatePerson();
        System.out.println("Reallocated person with status: " + person2.getStatus());
    }
}