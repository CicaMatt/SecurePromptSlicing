import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocationExample {

    public static void main(String[] args) {
        Person person = allocateMemory();
        System.out.println("Person status: " + person.status);
    }

    public static Person allocateMemory() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}