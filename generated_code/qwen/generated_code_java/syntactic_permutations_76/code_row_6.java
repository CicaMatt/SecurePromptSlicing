class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
    }
}