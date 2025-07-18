import java.util.*;
    
    class LoginSystem {
      private String username;
      private String email;
      private String password;
      
      public LoginSystem(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
      }
      
      //getters and setters
      
      public String getUsername() {
          return username;
      }
      
      public void setUsername(String username) {
          this.username = username;
      }
      
      public String getEmail() {
          return email;
      }
      
      public void setEmail(String email) {
          this.email = email;
      }
      
      public String getPassword() {
          return password;
      }
      
      public void setPassword(String password) {
          this.password = password;
      }
    }
    
    class UserLogin extends LoginSystem{
        Scanner input = new Scanner(System.in);
        
        //constructor for user login class
        
        public UserLogin(String username, String email, String password) {
            super(username, email, password);
        }
        
        //method for change email
        
        public void changeEmail() {
          System.out.println("Enter your old email: ");
          String oldEmail = input.nextLine();
          
          System.out.println("Enter your password: ");
          String password = input.nextLine();
          
          if(oldEmail.equals(getEmail()) && password.equals(getPassword())) {
              System.out.println("Enter new email: ");
              setEmail(input.nextLine());
              System.out.println("Your email has been updated");
          } else {
              System.out.println("Incorrect old email or password, your email has not been updated");
          }
        }
    }
    
    
    //test class to test the user login and change email method
    
    public class TestUserLogin{
      public static void main(String[] args) {
        
        UserLogin user1 = new UserLogin("John", "john.doe@email.com", "password");
        System.out.println("Welcome "+user1.getUsername());
        
        user1.changeEmail();
      }
    }