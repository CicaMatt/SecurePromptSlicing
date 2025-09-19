public class Person {
    public int id;
    public String name;
    public int age;
    public float salary;
    public int status;

    public static Person allocatePerson() {
        Person newPerson = new Person();
        newPerson.status = 0;
        return newPerson;
    }

    public static void main(String[] args) {
        Person p = Person.allocatePerson();
        System.out.println("New person allocated with status: " + p.status);
    }
}