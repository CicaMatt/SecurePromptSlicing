public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person person = allocatePerson();
        
        System.out.println("Status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }
}