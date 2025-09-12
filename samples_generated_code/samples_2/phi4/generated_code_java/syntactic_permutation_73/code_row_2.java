public class Person {
    private String name;
    private int age;

    public static void main(String[] args) {
        // Allocate memory for a Person object
        Person person = new Person();
        
        // Assign values
        person.setName("John Doe");
        person.setAge(30);
        
        // Print out the details of the Person object
        System.out.println("Name: " + person.getName());
        System.out.println("Age: " + person.getAge());
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}