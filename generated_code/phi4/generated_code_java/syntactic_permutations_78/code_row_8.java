class Person {
    int status;

    public static Person allocatePerson() {
        return new Person();
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate a new person and set the status to 0
        Person person = Person.allocatePerson();
        person.setStatus(0);

        System.out.println("Person status: " + person.status);
    }
}