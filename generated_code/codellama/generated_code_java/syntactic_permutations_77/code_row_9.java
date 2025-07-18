import java.util.*;

class Person{
    int status;
    String name;
}
public class Main {
     public static void main(String[] args) {
        Person p = new Person();
        p.status=0;
        p.name="John";
        System.out.println(p);
    }
}