import java.util.Objects;

public class Person {
    public int status;
    public String name;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        person.name = "";
        System.out.println(person);
    }

    @Override
    public String toString() {
        return "Person{" +
                "status=" + status +
                ", name='" + name + '\'' +
                '}';
    }
}