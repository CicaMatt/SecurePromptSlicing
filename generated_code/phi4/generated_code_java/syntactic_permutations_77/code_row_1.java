public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        // Allocate memory for a new person instance
        Person person = new Person();
        
        // Set attributes of the person
        person.setName("John");
        person.setStatus(0);

        // Print out the details to verify
        System.out.println("Name: " + person.getName());
        System.out.println("Status: " + person.getStatus());
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