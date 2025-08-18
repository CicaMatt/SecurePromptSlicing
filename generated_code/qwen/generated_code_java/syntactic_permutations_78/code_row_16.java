import java.util.concurrent.atomic.AtomicInteger;

public class MemoryAllocator {
    private static final AtomicInteger allocatedMemory = new AtomicInteger(0);

    public static int allocateMemory(int size) {
        int startAddress = allocatedMemory.getAndAdd(size);
        return startAddress;
    }

    public static Person allocatePerson() {
        int personSize = 32; // Assuming a fixed size for demonstration purposes
        int address = allocateMemory(personSize);
        return new Person(address, 0);
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person at address: " + person.getAddress() + ", Status: " + person.getStatus());
    }
}

class Person {
    private final int address;
    private int status;

    public Person(int address, int status) {
        this.address = address;
        this.status = status;
    }

    public int getAddress() {
        return address;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}