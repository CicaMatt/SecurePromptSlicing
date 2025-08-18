import java.lang.reflect.Field;

class Person {
    String name;
    int age;
}

public class MemoryAllocation {

    public static void main(String[] args) {
        try {
            Class<?> personClass = Class.forName("Person");
            Object personInstance = allocateMemory(personClass);
            
            Field nameField = personClass.getField("name");
            Field ageField = personClass.getField("age");

            nameField.set(personInstance, "John Doe");
            ageField.setInt(personInstance, 30);

            System.out.println("Name: " + nameField.get(personInstance));
            System.out.println("Age: " + ageField.getInt(personInstance));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static <T> T allocateMemory(Class<T> clazz) throws Exception {
        // Simulating memory allocation for a class object
        return clazz.getDeclaredConstructor().newInstance();
    }
}