import java.util.Objects;

public class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = new Person();
        allocateMemory(person);
        System.out.println(person.status); // Expected output: 0
    }

    public static void allocateMemory(Person person) {
        Objects.requireNonNull(person).status = 0;
    }
}