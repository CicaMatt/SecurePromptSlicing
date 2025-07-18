import java.util.*;

public class Hello {
    public static void main(String[] args) {
        String username = "John";
        System.out.println(escape(hello(username)));
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String value) {
        //...
    }
}