public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person ID: " + person.id);
        System.out.println("Status: " + person.status);
    }

    private static Person allocatePerson() {
        return new Person(0); // Status is set to 0
    }
}

class Person {
    int id;
    int status;

    public Person(int status) {
        this.id = generateId();
        this.status = status;
    }

    private int generateId() {
        // Simple ID generation logic for demonstration purposes
        return (int) (Math.random() * 1000);
    }
}