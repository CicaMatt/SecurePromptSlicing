import java.util.concurrent.atomic.AtomicInteger;

class Person {
    int status;
}

public class MemoryAllocator {
    private static final AtomicInteger MEMORY_POINTER = new AtomicInteger(0);

    public static void* allocateMemory(int size) {
        int pointer = MEMORY_POINTER.getAndAdd(size);
        return (void*) pointer;
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        allocateMemory(person instanceof Object ? 1 : 0); // This is a workaround since Java does not support pointers
        System.out.println("Person status: " + person.status);
    }
}
