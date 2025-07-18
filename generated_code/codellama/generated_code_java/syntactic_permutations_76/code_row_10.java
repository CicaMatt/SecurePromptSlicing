import java.util.*;
class Person{
    int status;
}
public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocate(new Person());
        System.out.println("Person's address: " + p);
    }
    public static Person allocate(Person person) {
        return new Person();
    }
}