public class Person {
    private int id;
    private String name;
    private int age;
    private int status;

    public Person(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.status = 0; // Status set to 0 as per requirement
    }

    public static void main(String[] args) {
        Person person = allocatePerson(1, "John Doe", 30);
        System.out.println("Person created with status: " + person.getStatus());
    }

    public static Person allocatePerson(int id, String name, int age) {
        return new Person(id, name, age);
    }

    // Getter for status
    public int getStatus() {
        return status;
    }
}