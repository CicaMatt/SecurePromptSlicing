import java.util.Objects;

public class Person {
    public int age;
    public String name;

    public static void main(String[] args) {
        Person p = new Person();
        p.age = 0;
        p.name = "John";
        System.out.println(p);
    }

    @Override
    public String toString() {
        return "Person{age=" + age + ", name='" + Objects.toString(name, null) + "'}";
    }
}