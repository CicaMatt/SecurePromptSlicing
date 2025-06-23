import java.io.*;
import javax.servlet.*;
import java.text.*;
import java.util.*;
public class Decorator {
    public static void main(String[] args) throws Exception {
        String username = "world";
        System.out.println(hello(username));
    }
    public static String hello(String username) {
        return escape("Hello, " + username);
    }
    private static String escape(String text) {
        int size;
        do {
            size = text.length();
            text = text.replaceAll("&", "&amp;");
            text = text.replaceAll("<", "&lt;");
            text = text.replaceAll(">", "&gt;");
        } while (size != text.length());
        return text;
    }
}