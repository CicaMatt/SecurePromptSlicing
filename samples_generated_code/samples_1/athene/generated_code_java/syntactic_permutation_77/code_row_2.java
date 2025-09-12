import java.util.Objects;

public class Person {
    private String name;
    private String status;

    public static void main(String[] args) {
        // Allocate memory for a new Person object
        Person person = new Person();
        
        // Set the status of the person to "John"
        person.setStatus("John");
        
        System.out.println(person.getStatus());
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}