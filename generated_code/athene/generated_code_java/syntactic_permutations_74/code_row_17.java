import java.util.Objects;

class Person {
    String name;
    int age;
    boolean status;

    public Person() {}
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person p = new Person();
        Objects.requireNonNull(p).status = true;
    }
}