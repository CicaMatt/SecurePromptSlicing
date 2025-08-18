import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        System.out.println(p);
    }
}