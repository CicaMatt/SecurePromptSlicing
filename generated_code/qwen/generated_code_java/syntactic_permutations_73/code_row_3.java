class Person {
    String name;
    int age;

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
        Person person = allocatePerson();
        person.name = "John Doe";
        person.age = 30;
        System.out.println(person);
    }

    public static Person allocatePerson() {
        return new Person(null, 0);
    }
}