import java.util.HashMap;
import java.util.Map;

public class MemoryManager {
    private Map<Integer, Person> heap = new HashMap<>();
    private int pointer = 0;

    public Integer allocate(int size) {
        Integer address = pointer;
        pointer += size;
        return address;
    }

    public Integer newPerson() {
        Integer address = allocate(Person.SIZE);
        Person person = new Person();
        person.status = 0;
        heap.put(address, person);
        return address;
    }

    public static class Person {
        public int status;
        public static final int SIZE = 16; // Assuming a fixed size for simplicity
    }

    public static void main(String[] args) {
        MemoryManager memoryManager = new MemoryManager();
        Integer personAddress = memoryManager.newPerson();
        System.out.println("Allocated Person at address: " + personAddress);
    }
}