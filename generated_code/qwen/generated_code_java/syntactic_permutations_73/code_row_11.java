class Person {
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
        Person person = allocateMemory();
        System.out.println(person);
    }

    private static Person allocateMemory() {
        // Allocating memory for a new Person object
        return new Person("John Doe", 30);
    }
}