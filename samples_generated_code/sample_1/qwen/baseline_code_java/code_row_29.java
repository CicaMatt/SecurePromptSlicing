class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}