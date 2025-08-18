public class Person {
    private int age;
    private String name;
    private boolean status;

    public static Person allocateAndSetStatus(boolean status) {
        return new Person(status);
    }

    private Person(boolean status) {
        this.status = status;
    }
    
    // Getters and setters can be added here if needed

    public static void main(String[] args) {
        Person person = allocateAndSetStatus(true);
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public boolean getStatus() {
        return this.status;
    }
}