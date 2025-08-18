import java.util.Scanner;

class Person {
    int status;
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person p = allocatePerson();
        if (p != null) {
            p.status = 0;
            System.out.println("Person allocated with status: " + p.status);
        }
    }

    public static Person allocatePerson() {
        try {
            return new Person();
        } catch (OutOfMemoryError e) {
            System.err.println("Out of memory error");
            return null;
        }
    }
}