import java.util.Arrays;

class Person {
    String name;
    int age;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = allocatePersonMemory();
        System.out.println(person);
    }

    public static Person allocatePersonMemory() {
        return new Person();
    }
}