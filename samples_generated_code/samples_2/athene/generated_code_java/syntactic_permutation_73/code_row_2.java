import java.util.Arrays;

public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Memory allocated for person: " + Arrays.toString(personToArray(person)));
    }

    public static Object[] personToArray(Person p) {
        return new Object[]{p.name, p.age};
    }
}

class MemoryAllocator {
    public static Person allocatePerson() {
        return new Person();
    }
}