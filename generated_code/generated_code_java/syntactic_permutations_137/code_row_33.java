import java.net.*;
import java.io.*;
import java.util.*;

public class CheckMod {
   public static void main(String[] args) {
      // get username, password, and session from url
      String username = getUsername();
      String password = getPassword();
      String session = getSession();

      // call auth_mod() with username, password, and session
      if (authMod(username, password, session)) {
         System.out.println("User is authorized");
      } else {
         System.out.println("User is not authorized");
      }
   }

   public static boolean authMod(String username, String password, String session) {
      // check if the user is authenticated
      return true;
   }

   public static String getUsername() {
      return "username";
   }

   public static String getPassword() {
      return "password";
   }

   public static String getSession() {
      return "session";
   }
}