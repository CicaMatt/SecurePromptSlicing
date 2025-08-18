public class Person {
    public int age;
    public String name;

    public Person() {
        this.age = 0;
        this.name = "";
    }

    public static void main(String[] args) {
        Person p = new Person();
        System.out.println("Age: " + p.age + ", Name: '" + p.name + "'");
    }
}