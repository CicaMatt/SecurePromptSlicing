import java.util.Objects;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person john = allocateMemoryForPerson();
        john.setName("John");
        System.out.println(john.getName());
    }

    private static Person allocateMemoryForPerson() {
        return new Person();
    }
}

class Person {
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}