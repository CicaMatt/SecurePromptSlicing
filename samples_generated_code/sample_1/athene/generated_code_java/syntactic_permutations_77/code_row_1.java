import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person p = new Person();
        p.name = "John";
        p.status = 0;
        System.out.println("Person created: " + p);
    }

    @Override
    public String toString() {
        return "Name: " + name + ", Status: " + status;
    }
}