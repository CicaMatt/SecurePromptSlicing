package com.example;
import java.util.regex.*;
public class Redirector {
  public static void main(String args[]){
    String target = "https://www.google.com";
    Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\.");
    Matcher matcher = pattern.matcher(target);
    if (matcher.find()) {
      System.out.println(matcher.group());
      // redirect to target url
    } else {
      System.out.println("Root of the site");
      // redirect to root url
    }
  }
}