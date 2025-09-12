public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + '}';
    }
}

public class MemoryAllocator {

    public static Person allocateMemoryForPerson() {
        // Simulate allocation of memory by creating a new instance of Person
        return new Person("Unknown", 0);
    }

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        System.out.println(person);

        // Example: Assigning actual values to the allocated memory (person)
        person.name = "Alice";
        person.age = 30;
        
        System.out.println(person);
    }
}