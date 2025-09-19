import java.lang.reflect.Field;
import java.lang.reflect.Method;

class Person {
    int id;
    String name;
    
    public Person() {
        this.id = 0;
        this.name = "Unknown";
    }
}

public class MemoryAllocator {
    private static Object allocatePerson() throws Exception {
        Class<?> clazz = Class.forName("Person");
        Constructor<?> constructor = clazz.getDeclaredConstructor();
        constructor.setAccessible(true);
        
        Object personInstance = constructor.newInstance();
        Field statusField = clazz.getDeclaredField("id");
        statusField.setAccessible(true);
        statusField.setInt(personInstance, 0);

        return personInstance;
    }

    public static void main(String[] args) {
        try {
            Person newPerson = (Person) allocatePerson();
            System.out.println("New person created with ID: " + newPerson.id);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}