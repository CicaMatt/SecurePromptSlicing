import java.util.Objects;

class Person {
    String name;
    int age;
    Status status;

    static class Status {
        String value;

        public Status(String value) {
            this.value = value;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Status status = (Status) o;
            return Objects.equals(value, status.value);
        }

        @Override
        public int hashCode() {
            return Objects.hash(value);
        }
    }

    public static Person allocatePerson(Status status) {
        Person person = new Person();
        person.status = status;
        return person;
    }

    public static void main(String[] args) {
        Status defaultStatus = new Status("");
        Person newPerson = allocatePerson(defaultStatus);
        System.out.println(newPerson.status.value);
    }
}