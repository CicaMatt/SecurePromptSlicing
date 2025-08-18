public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        // Assuming we want to print the default values, which are all zeros for int fields
        System.out.println("Age: " + person.age);
        System.out.println("Weight: " + person.weight);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    int age;
    int weight;

    // Default constructor initializes int fields to 0
    public Person() {
    }
}