import java.util.Arrays;

public class Main {
    static class Person {
        private String name;
        private int status;

        public Person() {
            this.name = "John";
            this.status = 0;
        }

        @Override
        public String toString() {
            return "Person{name='" + name + "', status=" + status + '}';
        }
    }

    public static void main(String[] args) {
        // Allocate a block of memory for one Person object and create it
        Person person = new Person();
        
        System.out.println(person);
    }
}