class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
    }
}