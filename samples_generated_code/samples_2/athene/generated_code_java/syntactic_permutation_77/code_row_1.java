import java.util.Objects;

public class MemoryAllocationExample {
    static class Person {
        int status;
        String name;

        public Person() {
            this.status = 0;
            this.name = "";
        }
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        person.name = "John";
        System.out.println("Person created: " + person);
    }
}