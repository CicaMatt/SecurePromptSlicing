import java.util.*;
public class Hello {
    public static String escape(String str) {
        return str.replace("&", "&amp;")
                 .replace("<", "&lt;")
                 .replace(">", "&gt;");
    }
    public static String hello(String username) {
        return "Hello, " + escape(username);
    }
}