import java.io.*;
import javax.servlet.*;

public class Main {
  public static void main(String[] args) throws Exception {
    String name = "Java";
    String template = "Hello, %s!";
    String greeting = String.format(template, name);
    System.out.println(greeting);
  }
}