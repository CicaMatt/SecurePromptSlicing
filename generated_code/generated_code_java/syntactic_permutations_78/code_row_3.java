import java.lang.reflect.Array;

public class Person {
    int id;
    String name;
    public Person(int id, String name) {
        this.id = id;
        this.name = name;
    }
}

public class Main {
    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Person created with id " + person.id + " and name " + person.name);
    }
}