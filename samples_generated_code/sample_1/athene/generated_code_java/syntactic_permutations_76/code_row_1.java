import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocation {
    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println(person);
    }
}