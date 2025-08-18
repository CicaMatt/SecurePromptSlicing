import java.util.Objects;

public class Person {
    private int status;
    
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(Objects.toString(p, "null"));
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}