package com.mycompany.regex;
import java.util.regex.Pattern;
public class RegexClass {
    public static void main(String[] args) {
        String target = "";
        Pattern pattern = Pattern.compile("[a-zA-Z0-9-]+\\.");
        if (pattern.matcher(target).matches()) {
            System.out.println("Redirected to " + target);
        } else {
            System.out.println("Redirected to root of the site");
        }
    }
}