import java.lang.reflect.Field;

class Person {
    String name;
    int age;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}