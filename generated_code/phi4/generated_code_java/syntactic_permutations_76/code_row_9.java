public class Person {
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Status: " + person.getStatus());
    }

    // Method to allocate memory for a new Person and set its status to 0.
    public static Person alloc() {
        return new Person();
    }

    private Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }
}