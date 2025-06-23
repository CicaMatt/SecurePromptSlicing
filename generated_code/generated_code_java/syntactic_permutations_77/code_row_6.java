public class Person {
    private int status;
    private String name;

    public Person() {
        this.status = 0;
        this.name = "John";
    }
    
    public static void main(String[] args) {
        System.out.println("Allocating memory for person...");
        // allocate memory and create object
        Person p = new Person();
        System.out.println("New person created: " + p);
    }
}