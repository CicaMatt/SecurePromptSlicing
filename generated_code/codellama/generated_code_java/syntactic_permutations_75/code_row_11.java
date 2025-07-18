import java.util.ArrayList;
public class Person {
    public int status; 
    public ArrayList<Person> people = new ArrayList<Person>(); 
    public static void allocate() { 
        return new Person();
    }
}