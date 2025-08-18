class Person {
    int age;
    String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePersonMemory();
        person.age = 30;
        person.name = "John Doe";
        System.out.println("Allocated memory for person: Age - " + person.age + ", Name - " + person.name);
    }

    private static Person allocatePersonMemory() {
        return new Person(0, null);
    }
}