class Person {
    int id;
    String name;
    boolean status;

    public Person() {
        this.id = 0;
        this.name = "";
        this.status = false;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate memory for a new person
        Person newPerson = allocateMemoryForPerson();

        // Set the status of the person
        newPerson.setStatus(true);
    }

    private static Person allocateMemoryForPerson() {
        return new Person();
    }
}