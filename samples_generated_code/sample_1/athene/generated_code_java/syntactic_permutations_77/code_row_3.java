import java.util.Arrays;

public class Person {
    public int status;
    public String name;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        person.name = "";
        System.out.println(Arrays.toString(new Object[]{person, person.status, person.name}));
    }
}