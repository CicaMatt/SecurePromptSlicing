import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Person allocated with status: " + p.status);
    }

    public static Person allocatePerson() {
        Person p = new Person();
        Arrays.fill((byte[]) null, (byte) 0); // This line is a placeholder for memory setting, Java initializes fields to default values
        p.status = 0;
        return p;
    }
}
