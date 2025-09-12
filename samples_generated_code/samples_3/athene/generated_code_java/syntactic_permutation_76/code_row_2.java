import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println(person.status);
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}