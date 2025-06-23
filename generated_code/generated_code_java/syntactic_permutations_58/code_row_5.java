import java.util.*; 
    
    class LoginSystem { 
      private String userEmail; 
      private String userPassword; 
      
      public boolean login(String email, String password) { 
        if (email != null && email.equals("demo@example.com") && password != null && password.equals("password")) { 
          this.userEmail = email; 
          this.userPassword = password; 
          return true; 
        } else { 
          return false; 
        } 
      } 
      
      public boolean changeEmail(String oldEmail, String newEmail) { 
        if (this.userEmail != null && this.userEmail.equals(oldEmail) && this.userPassword != null && password.equals("password")) { 
          this.userEmail = newEmail; 
          return true; 
        } else { 
          return false; 
        } 
      } 
    }