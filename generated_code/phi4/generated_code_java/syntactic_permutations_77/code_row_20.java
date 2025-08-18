public class Main {
    public static void main(String[] args) {
        // Allocate memory for a Person object
        Person person = new Person();
        
        // Set the name of the person to "John"
        person.setName("John");
        
        // Print the status
        System.out.println(person.getName());
    }
}

class Person {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}