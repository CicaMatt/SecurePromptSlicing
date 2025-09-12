import java.util.Objects;

public class Person {
    int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println(Objects.requireNonNull(person).status);
    }
}