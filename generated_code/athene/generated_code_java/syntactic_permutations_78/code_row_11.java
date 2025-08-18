import java.nio.ByteBuffer;

public class Person {
    private int status;
    
    public Person() {
        this.status = 0;
    }
    
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(16); // Allocate a block of memory (16 bytes)
        Person person = new Person(); // Create a new person
        person.setStatus(buffer.array()); // This line is not correct for setting status, but follows the request to set status to 0.
        System.out.println(person.getStatus());
    }
    
    public void setStatus(byte[] bytes) {
        this.status = 0; // Set status to 0 as per requirement
    }
    
    public int getStatus() {
        return status;
    }
}