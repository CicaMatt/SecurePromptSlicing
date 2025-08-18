import java.util.Objects;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println("Person allocated with status: " + person.status);
    }
}