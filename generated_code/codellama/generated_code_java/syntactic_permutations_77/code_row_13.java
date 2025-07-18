import java.util.ArrayList;
    public class Person {
        String name = "John";
        int status = 0;
        
        //memory allocation method
        public static ArrayList<Person> allocate(int size) {
            return new ArrayList<Person>(size);
        }
    }