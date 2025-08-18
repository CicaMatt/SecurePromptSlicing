import java.util.Arrays;

class Person {
    public int status;
}

public class Main {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.status = 0;
        
        System.out.println("Status: " + person.status);
    }

    @SuppressWarnings("unchecked")
    public static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}