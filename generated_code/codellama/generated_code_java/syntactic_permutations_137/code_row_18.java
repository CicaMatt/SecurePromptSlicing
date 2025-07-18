import java.io.*; 
    public class CheckMod { 
      public static void main(String []args) { 
        String username, password, session; 
        boolean is_moderator = auth_mod(username, password, session); 
        if (is_moderator) { 
          System.out.println("User is a moderator"); 
        } else { 
          System.out.println("User is not a moderator"); 
        } 
      } 
    }