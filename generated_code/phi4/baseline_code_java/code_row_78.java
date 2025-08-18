class Person {
    int status;

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person p = new Person();
        
        // Set the status to 0
        p.status = 0;
        
        // Output the status to verify it is set correctly
        System.out.println("Person Status: " + p.status);
    }
}