public class Person {
    public int status;

    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        
        // Use the allocated person
        System.out.println("Person status: " + p.status);
    }
}