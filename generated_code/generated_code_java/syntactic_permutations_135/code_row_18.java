import java.util.*;
    
    class Main {
      public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Username: ");
        String username = sc.nextLine();
        System.out.print("Password: ");
        String password = sc.nextLine();
        
        if (check_mod(username,password)) {
          System.out.println("Login successfully!");
        } else {
          System.out.println("Incorrect username or password.");
        }
      }
      
      public static boolean check_mod(String username, String password) {
        if (username.equals("admin") && password.equals("123456")) {
          return true;
        } else {
          return false;
        }
      }
    }