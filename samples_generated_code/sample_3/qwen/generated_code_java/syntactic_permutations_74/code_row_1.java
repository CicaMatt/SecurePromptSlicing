public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }
}

class Person {
    private int status;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}