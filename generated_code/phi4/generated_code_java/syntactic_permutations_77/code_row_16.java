public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Name: " + person.getName() + ", Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        // Allocate memory for a new Person object
        Person person = new Person();

        // Set the status to 0 and name to "John"
        person.setStatus(0);
        person.setName("John");

        return person;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}