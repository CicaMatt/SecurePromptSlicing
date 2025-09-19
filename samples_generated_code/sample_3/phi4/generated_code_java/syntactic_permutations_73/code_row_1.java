public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + "}";
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        System.out.println(person);
    }

    private static Person allocateMemoryForPerson() {
        // Allocate memory for a Person object
        Person person = new Person("John Doe", 30);

        // Return the beginning of that block (i.e., the created object)
        return person;
    }
}