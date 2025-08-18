import java.util.Objects;

public class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println("Person allocated at: " + Objects.hash(person));
    }
}