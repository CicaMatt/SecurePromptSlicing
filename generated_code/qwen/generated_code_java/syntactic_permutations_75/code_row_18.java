public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus('.');
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private char status;

    public char getStatus() {
        return status;
    }

    public void setStatus(char status) {
        this.status = status;
    }
}