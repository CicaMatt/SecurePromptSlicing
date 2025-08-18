import java.util.Objects;

public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Allocated person with status: " + Objects.requireNonNull(p).getStatus());
    }
}