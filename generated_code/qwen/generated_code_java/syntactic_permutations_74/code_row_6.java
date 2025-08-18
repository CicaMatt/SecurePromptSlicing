import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(new Person().getClass().getSize());
        Person person = new Person();
        setPersonStatus(buffer, person, 0);
        System.out.println("Person status: " + person.status);
    }

    private static void setPersonStatus(ByteBuffer buffer, Person person, int status) {
        person.status = status;
    }
}


Note: The method `getClass().getSize()` does not exist in Java. Instead, we allocate a fixed size of bytes for demonstration purposes. In actual practice, you would manage memory differently, possibly using native code or specific libraries like JNA or JNI for low-level memory manipulation. Here, the example is simplified and assumes such a method exists for illustration.