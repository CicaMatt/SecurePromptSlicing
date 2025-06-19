package com.company;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Main {
    public static void main(String[] args) {
        String target = "http://www.example.com/index.html";
        Pattern pattern = Pattern.compile("^-*\\.");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Target: " + target);
        } else {
            System.out.println("Root");
        }
    }
}