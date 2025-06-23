package com.techgaun.login;
import java.util.*;

class User {
    private String username,email,password;
    
    public User(String username, String email, String password){
        this.username = username;
        this.email = email;
        this.password = password;
    }
    
    public String getUsername(){
        return username;
    }
    
    public void setUsername(String username){
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
public class LoginService {
  private static final Map<User, User> users = new HashMap<User, User>();

  static {
    users.put(new User("John", "john@example.com", "secret"), new User("John","john.doe@example.com","secret"));
    users.put(new User("Jane", "jane@example.com", "janesecret"), new User("Jane","jane.doe@example.com","janesecret"));
  }
  
  public static boolean authenticateUser(String email, String password) {
    if (email == null || email.isEmpty()) return false;
    if (password == null || password.isEmpty()) return false;
    User user = new User("", email, password);
    User registeredUser = users.get(user);
    return user.equals(registeredUser);
  }
  
}
public class ChangeEmailPage {
    
        private String oldEmail;
        private String newEmail;
        private String confirmPassword;
        
        public void setOldEmail(String oldEmail){
            this.oldEmail = oldEmail;
        }
        
        public String getOldEmail(){
            return oldEmail;
        }
        
        public void setNewEmail(String newEmail){
            this.newEmail = newEmail;
        }
        
        public String getNewEmail(){
            return newEmail;
        }
        
        public void setConfirmPassword(String confirmPassword){
            this.confirmPassword = confirmPassword;
        }
        
        public String getConfirmPassword(){
            return confirmPassword;
        }
        
        public void changeEmail(){
            
            if(!LoginService.authenticateUser(oldEmail,confirmPassword)){
                System.out.println("Authentication failed");
                return;
            }
            
            User user = new User("",getOldEmail(),"");
            users.put(user,new User("", getNewEmail(), ""));
        }
}