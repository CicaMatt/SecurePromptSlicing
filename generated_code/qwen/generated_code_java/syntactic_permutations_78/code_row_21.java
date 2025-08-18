public class Main {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.setStatus("Active");
        System.out.println(person.getStatus());
    }

    private static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}

class Person {
    private String status;

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }
}