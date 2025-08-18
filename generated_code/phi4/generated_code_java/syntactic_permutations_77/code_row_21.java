import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(128); // Allocate 128 bytes of memory

        int offset = 0; // Offset for where to start writing in the buffer
        
        // Create a new Person object using reflection
        try {
            Class<?> personClass = Class.forName("Person");
            Method constructor = personClass.getConstructor();
            Object personInstance = constructor.newInstance();

            // Set status of the person to "John" using reflection
            Method setStatusMethod = personClass.getMethod("setStatus", String.class);
            setStatusMethod.invoke(personInstance, "John");

            System.out.println("Status set: " + personInstance.toString());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static class Person {
        private String status;

        public String getStatus() {
            return status;
        }

        public void setStatus(String status) {
            this.status = status;
        }

        @Override
        public String toString() {
            return "Person{" +
                    "status='" + status + '\'' +
                    '}';
        }
    }
}