import java.io.*;
import java.util.Scanner;

public class check_mod {
     public static void main(String args[]){
        String username = args[0];
        String password = args[1];
        String session = args[2];
        boolean result = auth_mod(username,password,session);
        if(result == true){
            System.out.println("User is a moderator");
        }else{
            System.out.println("User is not a moderator");
        }
    }
     public static boolean auth_mod(String username, String password, String session) {
         if (username.equals("admin") && password.equals("password123") && session.equals("sessionID")){
            return true;
          }else{
              return false;
          }
     }
}