import java.util.Objects;

public class Person {
    private int status;

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return status == person.status;
    }

    @Override
    public int hashCode() {
        return Objects.hash(status);
    }
}