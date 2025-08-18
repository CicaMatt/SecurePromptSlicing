public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person john = allocateMemoryForPerson();
        john.setStatus(0);
        john.setName("John");
    }

    private static Person allocateMemoryForPerson() {
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