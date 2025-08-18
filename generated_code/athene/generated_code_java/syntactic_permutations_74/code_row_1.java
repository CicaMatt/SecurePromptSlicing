import java.util.Objects;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.status); // Should print 0
    }

    public static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }
}