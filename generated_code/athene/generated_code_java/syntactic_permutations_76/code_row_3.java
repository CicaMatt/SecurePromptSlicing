import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println(Arrays.toString(new Object[]{person, person.status}));
    }
}