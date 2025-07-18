import java.util.Objects;

class Person {
    public static Person allocate(int size) {
        return new Person(size, 0, "John");
    }

    private final int size;
    private final int status;
    private final String name;

    public Person(int size, int status, String name) {
        this.size = size;
        this.status = status;
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Person)) return false;
        Person person = (Person) o;
        return size == person.size && status == person.status && Objects.equals(name, person.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(size, status, name);
    }
}