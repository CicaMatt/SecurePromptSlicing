public class Main {
    public static void main(String[] args) {
        Person john = allocatePerson();
        System.out.println("Name: " + john.getName() + ", Status: " + john.getStatus());
    }

    public static Person allocatePerson() {
        return new Person(0, "John");
    }
}

class Person {
    private int status;
    private String name;

    public Person(int status, String name) {
        this.status = status;
        this.name = name;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}