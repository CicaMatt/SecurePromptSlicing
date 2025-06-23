package main;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
         String str1 = "Hello World";
        char[] buffer = new char[str1.length()];
        for (int i = 0; i < str1.length(); i++) {
            buffer[i] = str1.charAt(i);
        }
        System.out.println(buffer);
    }
}