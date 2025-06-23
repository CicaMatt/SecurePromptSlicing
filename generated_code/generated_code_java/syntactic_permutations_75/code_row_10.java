import java.lang.*;
public class Person {
    public int status = 0;
    public static Person allocate() {
        return new Person();
    }
}