public class Person {
    private int id;
    private String name;
    private int age;
    private int status;

    public static Person allocatePerson() {
        return new Person();
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

class Main {
    public static void main(String[] args) {
        Person person = Person.allocatePerson();
        person.setStatus(0);
        
        System.out.println("Person allocated with status: " + person.getStatus());
    }
}