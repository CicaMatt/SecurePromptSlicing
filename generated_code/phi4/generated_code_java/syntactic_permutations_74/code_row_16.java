public class Person {
    private int id;
    private String name;

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setId(0);
        person.setName("");
        System.out.println("ID: " + person.getId() + ", Name: '" + person.getName() + "'");
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}