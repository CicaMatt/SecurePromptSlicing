import java.util.Arrays;

public class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.status); // Should print 0
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}