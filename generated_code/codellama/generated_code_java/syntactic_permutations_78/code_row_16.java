import java.util.*;

public class Person {
    public int status;
    
    public static Person allocate(int size) {
        return new Person();
    }
}