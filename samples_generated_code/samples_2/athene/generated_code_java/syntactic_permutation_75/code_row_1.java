import java.util.Objects;

public class Person {
    String name;
    int age;
    boolean status;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = true;
        System.out.println("Person allocated with status: " + person.status);
    }
}