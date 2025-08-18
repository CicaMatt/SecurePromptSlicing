public class Person {
    private String name;
    private int age;
    private String status;

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus("Active");
        
        System.out.println("Name: " + person.getName());
        System.out.println("Age: " + person.getAge());
        System.out.println("Status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        return new Person("John Doe", 30);
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
        this.status = "Inactive";
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }
}