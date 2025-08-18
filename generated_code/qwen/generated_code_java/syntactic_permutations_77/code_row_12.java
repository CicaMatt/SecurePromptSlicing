public class Main {
    public static void main(String[] args) {
        Person john = allocateMemory();
        System.out.println("Name: " + john.name + ", Status: " + john.status);
    }

    public static Person allocateMemory() {
        return new Person("John", 0);
    }
}

class Person {
    String name;
    int status;

    Person(String name, int status) {
        this.name = name;
        this.status = status;
    }
}