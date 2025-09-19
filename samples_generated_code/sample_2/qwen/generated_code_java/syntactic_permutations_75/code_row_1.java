public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }
}