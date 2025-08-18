public class Person {
    int status;

    public static void main(String[] args) {
        // Allocate memory for a Person object and set status to 0
        Person p = new Person();
        p.status = 0;
        
        // Example usage: Print the status of the person
        System.out.println("Person status: " + p.status);
    }
}