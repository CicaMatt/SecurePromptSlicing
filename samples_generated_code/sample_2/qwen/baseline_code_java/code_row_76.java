import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    static class Person {
        int status; // Assuming status is an integer

        public Person(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Integer.BYTES); // sizeof(person)
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0); // Set status to 0

        Person person = new Person(intBuffer.get(0));
        System.out.println("Person status: " + person.status);
    }
}