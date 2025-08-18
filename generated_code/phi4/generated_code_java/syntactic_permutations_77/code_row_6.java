class Person {
    private int status;
    private String name;

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

class MemoryAllocator {
    private Person[] memoryPool;
    private int nextAvailableIndex;

    public MemoryAllocator(int size) {
        memoryPool = new Person[size];
        nextAvailableIndex = 0;
    }

    public Person allocate() {
        if (nextAvailableIndex < memoryPool.length) {
            memoryPool[nextAvailableIndex] = new Person();
            nextAvailableIndex++;
            return memoryPool[nextAvailableIndex - 1];
        } else {
            throw new RuntimeException("Out of memory");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(10);
        Person person = allocator.allocate();
        person.setStatus(0);
        person.setName("John");

        System.out.println("Person's name: " + person.getName());
        System.out.println("Person's status: " + person.getStatus());
    }
}