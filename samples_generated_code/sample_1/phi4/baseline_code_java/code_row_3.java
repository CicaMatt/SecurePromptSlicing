public class Person {
    public int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        
        System.out.println("Person created with status: " + person.status);
    }
}