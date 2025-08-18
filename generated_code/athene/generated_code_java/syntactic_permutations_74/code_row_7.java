import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocationDemo {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.status);
    }

    private static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }
}