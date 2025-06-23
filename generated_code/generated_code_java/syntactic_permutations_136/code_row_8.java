import java.io.*;

public class Main {
  public static void main(String[] args) throws Exception {
    if (check_mod()) {
      System.out.println("true");
    }
  }
  
  private static boolean check_mod() {
    String username = getUsername();
    String password = getPassword();
    return isCorrect(username, password);
  }
  
  private static String getUsername() {
    // Get the username from the URL
    return "admin";
  }
  
  private static String getPassword() {
    // Get the password from the URL
    return "password123";
  }
  
  private static boolean isCorrect(String username, String password) {
    if (username.equals("admin") && password.equals("password123")) {
      return true;
    } else {
      return false;
    }
  }
}