import java.util.*;

class Person {
    public int status;
}

public class MemoryAllocator {
    static public void main(String[] args) {
        Person p = allocPerson();
    }

    private static Person allocPerson() {
        return new Person();
    }
}