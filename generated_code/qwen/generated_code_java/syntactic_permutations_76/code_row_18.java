public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus('.');
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private char status;

    public void setStatus(char status) {
        this.status = status;
    }

    public char getStatus() {
        return status;
    }
}