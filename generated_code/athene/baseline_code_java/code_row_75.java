import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocationDemo {
    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        System.out.println("Person allocated with status: " + p.status);
    }
}