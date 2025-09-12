import java.util.Objects;

public class Person {
    private int status;

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }

    public int getStatus() {
        return status;
    }

    private void setStatus(int status) {
        this.status = status;
    }
}