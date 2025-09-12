public class Person {
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Person Status: " + person.getStatus());
    }

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }
}