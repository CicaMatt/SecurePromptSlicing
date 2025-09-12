public class Main {
    public static void main(String[] args) {
        Person person = (Person) allocate();
        System.out.println("Name: " + person.name);
        System.out.println("Status: " + person.status);
    }

    // Allocates a block of memory for a new Person and sets the status to 0
    public static Object allocate() {
        return new Person(0);
    }
}

class Person {
    String name;
    int status;

    public Person(int initialStatus) {
        this.name = "Default Name";
        this.status = initialStatus;
    }
}