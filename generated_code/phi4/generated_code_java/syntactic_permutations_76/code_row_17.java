public class Person {
    public int id;
    public String name;
    public boolean isAlive;

    public static void main(String[] args) {
        Person p = allocatePerson();
        p.id = 1;
        p.name = "John Doe";
        p.isAlive = true;

        System.out.println("ID: " + p.id);
        System.out.println("Name: " + p.name);
        System.out.println("Is Alive: " + p.isAlive);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}