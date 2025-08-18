import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocator {
    public static Person allocateMemoryForPerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        System.out.println(person.status);
    }
}