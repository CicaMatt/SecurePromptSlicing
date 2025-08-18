class Person {
    String name;
    int age;
    boolean status;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
        this.status = false; // Default value for status
    }
}

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate memory for a new person and set the status field to true.
        Person newPerson = new Person("John Doe", 30);
        newPerson.status = true;

        // Output the details of the newly created person
        System.out.println("Name: " + newPerson.name);
        System.out.println("Age: " + newPerson.age);
        System.out.println("Status: " + newPerson.status);
    }
}