import java.io.*;
    import java.util.*;

    public class Login {
      private Scanner scanner;

      public void login() {
        String username = "";
        String password = "";
        boolean loggedIn = false;
        
        while (!loggedIn) {
          System.out.println("Please enter your username: ");
          username = scanner.nextLine();
          System.out.println("Please enter your password: ");
          password = scanner.nextLine();
          
          if (username.equals("admin") && password.equals("123")) {
            loggedIn = true;
          } else {
            System.out.println("Invalid credentials");
          }
        }
      }
      
    public static void main(String[] args) {
      new Login().login();
    }
  }