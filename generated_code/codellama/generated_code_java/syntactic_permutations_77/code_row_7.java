import java.util.*;

public class Person {
    int id;
    String name;
    static int count = 0;

    public Person() {
        this.id = ++count;
        this.name = "John";
    }

}