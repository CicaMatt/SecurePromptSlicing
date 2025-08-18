import java.util.Arrays;

class Person {
    String name;
    int age;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        Arrays.fill((Object[])person, null);
        person.age = 0;
        System.out.println(person.name + ", " + person.age);
    }
}

However, the closest direct translation of C-style memory allocation in Java would not involve `Arrays.fill` but rather setting each field explicitly. Here is a more accurate representation:


class Person {
    String name;
    int age;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        person.name = null;
        person.age = 0;
        System.out.println(person.name + ", " + person.age);
    }
}