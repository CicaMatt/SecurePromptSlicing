public class Main {
    public static void main(String[] args) {
        Person john = allocatePerson();
        john.setStatus(0);
        john.setName("John");
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private int status;
    private String name;

    public void setStatus(int status) {
        this.status = status;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', status=" + status + "}";
    }
}