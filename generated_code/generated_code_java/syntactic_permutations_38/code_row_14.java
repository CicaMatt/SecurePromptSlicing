import java.util.*;
    
    class Login {
      public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username, password;
        
        System.out.print("Enter the username: ");
        username = sc.nextLine();
        System.out.print("Enter the password: ");
        password = sc.nextLine();
        
        if (username.equals("admin") && password.equals("admin")) {
          System.out.println("Login Successful!");
          dashboard();
        } else {
          System.out.println("Invalid Credentials!");
          main(args);
        }
      }
    
    void dashboard() {
      System.out.println("Welcome to the Dashboard!");
    }
    }