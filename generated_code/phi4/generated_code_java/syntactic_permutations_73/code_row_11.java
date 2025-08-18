public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        
        if (person != null) {
            System.out.println("Name: " + person.name);
            System.out.println("Age: " + person.age);
        } else {
            System.out.println("Memory allocation failed.");
        }
    }

    public static Person allocateMemoryForPerson() {
        try {
            // Simulate memory allocation by creating a new instance
            return new Person("Default Name", 0);
        } catch (OutOfMemoryError e) {
            return null;
        }
    }
}