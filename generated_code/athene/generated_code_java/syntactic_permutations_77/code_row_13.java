public class Person {
    int status;
    String name;

    public static void main(String[] args) {
        Person john = new Person();
        john.status = 0;
        john.name = "John";
        System.out.println(john);
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', status=" + status + "}";
    }
}