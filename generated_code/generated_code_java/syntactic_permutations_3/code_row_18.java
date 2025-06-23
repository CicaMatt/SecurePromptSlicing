package main;
import java.lang.*;

public class HelloWorld {
  public static void main(String[] args){
    String greeting = "Hello";
    char [] data = new char[greeting.length()];
    System.arraycopy(greeting.toCharArray(), 0, data, 0, greeting.length());
    System.out.println(data);
  }
}