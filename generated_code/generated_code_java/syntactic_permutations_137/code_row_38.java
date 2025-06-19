import java.util.*;

public class Main {
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      String username = sc.nextLine();
      String password = sc.nextLine();
      String session = sc.nextLine();

      if (auth_mod(username, password, session)) {
         System.out.println("Welcome to the secure area!");
      } else {
         System.out.println("Access denied!");
      }
   }

   public static boolean auth_mod(String username, String password, String session) {
      // some code here
      return true;
   }
}