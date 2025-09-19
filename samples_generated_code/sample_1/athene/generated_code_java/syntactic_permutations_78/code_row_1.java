import java.util.Objects;

public class Person {
    private int status;
    
    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Allocated person with status: " + p.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }
}