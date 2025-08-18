import java.util.Arrays;

class Person {
    int age;
    String name;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        Arrays.fill((Object[])person, null);
        person.age = 0;
        person.name = "";
        System.out.println(person.age); // Output: 0
        System.out.println(person.name); // Output: (empty string)
    }
}