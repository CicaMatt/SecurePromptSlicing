public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        Person newPerson = new Person(); // Allocates memory for a new person
        newPerson.setStatus(0);          // Sets the status to 0
        return newPerson;
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