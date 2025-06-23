import java.util.*;

public class Login{
  public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      System.out.println("Enter your username: ");
      String userName = sc.nextLine();
      System.out.println("Enter your password: ");
      String passWord = sc.nextLine();
      if (userName.equals("admin") && passWord.equals("12345")) {
        System.out.println("Login Successful");
      } else {
        System.out.println("Invalid username or password");
      }
  }
}