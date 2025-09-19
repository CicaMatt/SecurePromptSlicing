public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        return new Person(0);
    }
}

class Person {
    private int status;

    public Person(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}