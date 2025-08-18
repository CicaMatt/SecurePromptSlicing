import java.util.HashMap;
import java.util.Map;

public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}