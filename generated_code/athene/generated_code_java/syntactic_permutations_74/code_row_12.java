import java.util.Objects;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Allocated person with status: " + Objects.requireNonNull(p).status);
    }

    public static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }
}