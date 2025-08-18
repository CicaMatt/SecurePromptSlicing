public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Name: " + person.getName() + ", Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person("John", 0);
    }
}

class Person {
    private String name;
    private int status;

    public Person(String name, int status) {
        this.name = name;
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public int getStatus() {
        return status;
    }
}