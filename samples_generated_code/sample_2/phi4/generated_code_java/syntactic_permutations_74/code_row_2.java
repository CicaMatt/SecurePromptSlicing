public class Person {
    int age;
    String name;
    boolean status;

    public static void main(String[] args) {
        Person person = new Person();
        initializePerson(person);
        System.out.println("Name: " + person.name + ", Age: " + person.age + ", Status: " + person.status);
    }

    private static void initializePerson(Person person) {
        // Simulate allocation and initialization
        person.age = 0;
        person.name = "";
        person.status = false; // status field set to 0 (false)
    }
}