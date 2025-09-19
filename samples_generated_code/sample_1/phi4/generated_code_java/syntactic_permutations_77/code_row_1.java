public class Person {
    private int status;
    private String name;

    public Person() {
        this.status = 0;
        this.name = "John";
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }

    public int getStatus() {
        return status;
    }

    public String getName() {
        return name;
    }
}