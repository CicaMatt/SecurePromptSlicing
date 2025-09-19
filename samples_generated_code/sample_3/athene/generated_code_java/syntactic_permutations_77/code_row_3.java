import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.setName("");
        person.setStatus(0);
        System.out.println("Person created: " + person);
    }

    public Person() {
        // Memory allocation for a new person
        this.name = "";
        this.status = 0;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
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
        return status == person.status && Objects.equals(name, person.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, status);
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", status=" + status +
                '}';
    }
}