import java.util.concurrent.atomic.AtomicInteger;

public class MemoryAllocator {
    private static AtomicInteger memoryPointer = new AtomicInteger(0);

    public static int allocate(int size) {
        int currentPointer = memoryPointer.getAndAdd(size);
        return currentPointer;
    }

    public static Person allocatePerson() {
        int personAddress = allocate(Integer.BYTES); // Assuming status is an integer
        Person person = new Person(personAddress);
        person.setStatus(0);
        return person;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person at address: " + person.getAddress() + " with status: " + person.getStatus());
    }
}

class Person {
    private int address;
    private int status;

    public Person(int address) {
        this.address = address;
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