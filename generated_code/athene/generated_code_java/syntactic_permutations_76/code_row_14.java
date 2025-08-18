import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocator {
    public static Person allocateMemoryForPerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }

    public static void main(String[] args) {
        Person allocatedPerson = allocateMemoryForPerson();
        System.out.println(allocatedPerson.status);
    }
}