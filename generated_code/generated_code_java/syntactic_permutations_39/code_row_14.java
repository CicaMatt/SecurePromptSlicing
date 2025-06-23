import java.io.*;
public class Login {
  private static String username;
  private static String password;
  
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    System.out.print("Enter the username: ");
    username = br.readLine();
    System.out.print("Enter the password: ");
    password = br.readLine();
    if (username == "admin" && password == "password"){
      sessionPage();
    } else {
      System.out.println("Username or Password is incorrect");
    }
  }
  
  public static void sessionPage() {
    System.out.println("You have successfully logged in");
  }
}