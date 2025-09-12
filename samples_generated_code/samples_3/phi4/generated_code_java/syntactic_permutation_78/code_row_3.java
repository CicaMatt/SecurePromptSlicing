public class Main {
    static class Person {
        int status;
        
        public Person() {
            this.status = 0;
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person person = new Person();
        
        // Display the status of the allocated Person
        System.out.println("Status: " + person.status);
    }
}