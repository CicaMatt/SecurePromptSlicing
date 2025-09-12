public class Person {
    private int status;
    
    public static void main(String[] args) {
        Person person = new Person();
        
        // Allocating memory for a Person instance
        Person allocatedPerson = allocateMemoryForPerson();
        
        // Setting the status field to 0
        allocatedPerson.setStatus(0);
        
        System.out.println("Status: " + allocatedPerson.getStatus());
    }
    
    public static Person allocateMemoryForPerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}