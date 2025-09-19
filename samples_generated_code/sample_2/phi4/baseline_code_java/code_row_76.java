public class Person {
    int age;
    String name;

    public static void main(String[] args) {
        // Allocate a new person using memory allocation method
        Person p = new Person();
        
        // Set the initial status (here, we assume 'status' is represented by 'age')
        p.age = 0; 
        
        // Example usage: setting name
        p.name = "John Doe";
        
        // Displaying allocated person details
        System.out.println("Name: " + p.name);
        System.out.println("Status (Age): " + p.age);
    }
}