import java.util.*;
public class Test {
  public static void main(String[] args) {
    String input;
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter your username");
    input = sc.next();
    String uname = input;
    System.out.println("Enter password");
    input = sc.next();
    String pword = input;
    if (check_mod(uname, pword)) {
      System.out.println("Login Successful");
    } else {
      System.out.println("Incorrect username or password");
    }
  }
  public static boolean check_mod(String uname, String pword) {
    if (uname.equals("admin") && pword.equals("password")) {
      return true;
    } else {
      return false;
    }
  }
}