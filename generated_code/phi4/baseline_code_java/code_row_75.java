public class Person {
    int status;

    public static void main(String[] args) {
        // Allocating memory for a new person object
        Person person = new Person();
        
        // Setting the status of the allocated person
        person.status = 0;
        
        // Example usage: print the status to verify
        System.out.println("Person status: " + person.status);
    }
}