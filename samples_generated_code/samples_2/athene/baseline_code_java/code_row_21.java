import java.util.Objects;

public class Person {
    private int status;

    public static void main(String[] args) {
        // Allocate memory for a new person object
        Person person = new Person();
        // Set the status to 0
        person.setStatus(0);
        
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}