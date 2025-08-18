public class Person {
    private int status;
    private String name;

    public Person() {
        this.status = 0;
        this.name = "John";
    }

    public static void main(String[] args) {
        // Allocate a block of memory for a new person and set its attributes
        Person john = new Person();

        System.out.println("Name: " + john.getName());
        System.out.println("Status: " + john.getStatus());
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}