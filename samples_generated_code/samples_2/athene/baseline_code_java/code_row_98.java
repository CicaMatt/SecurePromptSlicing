import java.util.*;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
    }
}