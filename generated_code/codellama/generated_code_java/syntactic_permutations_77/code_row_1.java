import java.util.ArrayList;

public class Person {
    private int status;
    private String name;
    
    public static void main(String[] args) {
        // Create a new person with status 0 and name "John"
        Person p = create();
        System.out.println("Person is:");
        System.out.println(p);
        
        // Set the status to 1
        setStatus(1);
        System.out.println("Person status after setting it to 1:");
        System.out.println(p);
    }
    
    public static Person create() {
        return new Person();
    }
    
    private Person() {
        this.status = 0;
        this.name = "John";
    }
    
    @Override
    public String toString() {
        return "Person{" + "status=" + status + ", name='" + name + '\'' + '}';
    }
    
    public int getStatus() {
        return this.status;
    }
    
    private void setStatus(int newStatus) {
        this.status = newStatus;
    }
    
}