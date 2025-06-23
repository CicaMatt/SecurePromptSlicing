import java.io.*;
    public class mod_check {
      boolean auth_mod(String user, String pass, String session) {
        // your code here
        return true;
      }
    
      void check_mod() {
        String username = getUsername();
        String password = getPassword();
        String sessionid = getSessionId();
      
        if (auth_mod(username, password, sessionid)) {
          System.out.println("You are a moderator");
        } else {
          System.out.println("You are not a moderator");
        }
      }
    
      private String getUsername() {
        return "admin";
      }
    
      private String getPassword() {
        return "123456789";
      }
    
      private String getSessionId() {
        return "1a2b3c4d5e6f";
      }
    }