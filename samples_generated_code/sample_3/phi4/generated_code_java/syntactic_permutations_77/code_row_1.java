class Person {
    int status;
    String name;

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person person = new Person();

        // Set status to 0 and name to "John"
        person.status = 0;
        person.name = "John";

        // Output the details of the person
        System.out.println("Status: " + person.status);
        System.out.println("Name: " + person.name);
    }
}