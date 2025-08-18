public class Person {
    private int id;
    
    public static void main(String[] args) {
        // Allocate a new Person object
        Person person = new Person();
        
        // Set the ID to 0
        person.setId(0);
        
        // Display the ID to verify it's set correctly
        System.out.println("Person ID: " + person.getId());
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}