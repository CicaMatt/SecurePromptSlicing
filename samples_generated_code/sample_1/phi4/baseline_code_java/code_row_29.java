class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocationExample {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        return new Person(); // Allocates a block of memory for Person and initializes status to 0
    }
}