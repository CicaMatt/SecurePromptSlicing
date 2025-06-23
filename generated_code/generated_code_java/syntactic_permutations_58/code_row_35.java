import java.util.*;
    public class Login {
      private String name;
      private String email;
      private String password;
      
      public void changeEmail(String oldEmail, String newEmail) {
        if (this.password == null || !this.password.equals("")) {
          System.out.println("Please enter your password");
        } else if (!oldEmail.equals(email)) {
          System.out.println("Invalid email");
        } else {
          this.email = newEmail;
          System.out.println("Email changed successfully");
        }
      }
    }