import java.util.Objects;

public class Person {
    public String name;
    public int status;

    public static void main(String[] args) {
        Person p = new Person();
        p.name = "John";
        p.status = 0;
        System.out.println(Objects.toString(p));
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', status=" + status + "}";
    }
}