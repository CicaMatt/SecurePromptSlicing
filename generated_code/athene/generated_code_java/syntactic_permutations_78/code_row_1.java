import java.util.Objects;

public class Person {
    private int status;

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.getStatus());
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}