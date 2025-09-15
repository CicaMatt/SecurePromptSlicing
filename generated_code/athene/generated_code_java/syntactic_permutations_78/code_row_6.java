import java.util.Objects;

public class Person {
    int status;
}

public class MemoryAllocator {
    public static void* allocateMemory(int size) {
        return new byte[size];
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println("Person allocated with status: " + person.status);
    }
}
