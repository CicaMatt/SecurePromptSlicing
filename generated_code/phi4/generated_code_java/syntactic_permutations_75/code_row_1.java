public class Person {
    private int status;

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person person = allocatePerson();
        
        // Set initial status (already set to 0 in allocatePerson)
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }
}