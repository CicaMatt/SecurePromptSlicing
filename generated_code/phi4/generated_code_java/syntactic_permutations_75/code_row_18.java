public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        // Allocate memory for a new person using 'new' keyword in Java
        Person person = new Person();
        
        // Set attributes for the allocated person object (assuming status is represented by these fields)
        person.name = "John Doe";
        person.age = 30;

        // Example usage of the allocated and initialized person object
        System.out.println("Person Name: " + person.name);
        System.out.println("Person Age: " + person.age);
    }
}