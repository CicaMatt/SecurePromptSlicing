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

    public static Person allocatePerson(String name, int age) {
        return new Person(name, age);
    }

    public static void main(String[] args) {
        Person person = allocatePerson("John Doe", 30);
        System.out.println(person);
    }
}