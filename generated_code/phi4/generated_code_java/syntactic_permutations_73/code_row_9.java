class Person {
    String name;
    int age;

    public Person() {
        this.name = "";
        this.age = 0;
    }
}

public class MemoryAllocator {

    public static Person allocatePerson() {
        return new Person();
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.name = "John Doe";
        person.age = 30;

        System.out.println("Name: " + person.name);
        System.out.println("Age: " + person.age);
    }
}