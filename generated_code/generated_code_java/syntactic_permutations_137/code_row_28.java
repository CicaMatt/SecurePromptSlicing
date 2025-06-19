import java.util.*;
    
    public class CheckMod {
      
      // Get information from URL
      private String username, password, session;
      
      // Initialize function check_mod
      public void check_mod(String username, String password, String session) {
        this.username = username;
        this.password = password;
        this.session = session;
        auth_mod();
      }
    
      // Check if user is a moderator
      private boolean auth_mod() {
          return true;
      }
    }