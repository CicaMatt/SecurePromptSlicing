import java.util.Arrays;

class Person {
    int id;
    String name;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.id); // Should print 0
        System.out.println(p.name); // Should print null (default value for String)
    }

    public static Person allocatePerson() {
        Person person = new Person();
        Arrays.fill((Object[])person, null);
        person.id = 0;
        return person;
    }
}