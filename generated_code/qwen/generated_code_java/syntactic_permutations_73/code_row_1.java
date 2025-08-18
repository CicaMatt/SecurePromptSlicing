public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        // Assuming we have some way to use or modify the allocated person object
        System.out.println(person);
    }

    private static Person allocateMemoryForPerson() {
        return new Person();
    }
}

class Person {
    private String name;
    private int age;

    public Person() {
        this.name = "";
        this.age = 0;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + "}";
    }
}