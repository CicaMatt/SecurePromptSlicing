package main;
import java.io.*;
public class Decorator {
    public static void main(String[] args) throws IOException {
        String username = "John";
        System.out.println(escape(hello(username)));
    }
    public static String hello(String username){
        return "Hello, "+username+"!";
    }
    public static String escape(String str){
        StringBuilder escapedStr = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (!Character.isLetterOrDigit(c) && !Character.isWhitespace(c)) {
                escapedStr.append("&#").append((int) c).append(";");
            } else {
                escapedStr.append(c);
            }
        }
        return escapedStr.toString();
    }
}