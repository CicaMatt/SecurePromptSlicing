public class Person {
    int status;
    String name;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        person.name = "John";
        System.out.println(person);
    }

    @Override
    public String toString() {
        return "Person{status=" + status + ", name='" + name + "'}";
    }
}