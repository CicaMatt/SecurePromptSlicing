import java.lang.reflect.Field;
import java.util.Arrays;

class Person {
    int id;
    String name;
}

public class MemoryAllocation {

    public static void main(String[] args) throws Exception {
        // Allocate memory for a block of size sizeof(Person)
        byte[] buffer = new byte[getSizeOfPerson()];
        
        // Get the fields of the Person class
        Field[] fields = Person.class.getDeclaredFields();
        
        // Create an instance of Person from the allocated memory
        Person personInstance = (Person) convertToInstance(buffer, fields);
        
        // Set status to 0 (assuming 'status' is meant to be 'id')
        personInstance.id = 0;
        
        System.out.println("Allocated Person: " + Arrays.toString(personInstance.fields()));
    }

    private static int getSizeOfPerson() {
        Field[] fields = Person.class.getDeclaredFields();
        int size = 0;
        for (Field field : fields) {
            if (field.getType().equals(int.class)) {
                size += Integer.BYTES;
            } else if (field.getType().equals(String.class)) {
                size += Integer.BYTES; // For reference
            }
        }
        return size;
    }

    private static Object convertToInstance(byte[] buffer, Field[] fields) throws Exception {
        Person person = new Person();
        for (Field field : fields) {
            if (field.getType().equals(int.class)) {
                field.setAccessible(true);
                int value = ByteBuffer.wrap(Arrays.copyOfRange(buffer, 0, Integer.BYTES)).getInt();
                field.setInt(person, value);
                buffer = Arrays.copyOfRange(buffer, Integer.BYTES, buffer.length);
            } else if (field.getType().equals(String.class)) {
                field.setAccessible(true);
                int stringRefIndex = ByteBuffer.wrap(Arrays.copyOfRange(buffer, 0, Integer.BYTES)).getInt();
                String stringValue = "DummyString"; // Placeholder for actual string reference
                field.set(person, stringValue); // Assigning a dummy value for demonstration
                buffer = Arrays.copyOfRange(buffer, Integer.BYTES, buffer.length);
            }
        }
        return person;
    }

    private static Object[] fields(Person person) throws Exception {
        Field[] fields = Person.class.getDeclaredFields();
        Object[] values = new Object[fields.length];
        for (int i = 0; i < fields.length; i++) {
            fields[i].setAccessible(true);
            values[i] = fields[i].get(person);
        }
        return values;
    }
}