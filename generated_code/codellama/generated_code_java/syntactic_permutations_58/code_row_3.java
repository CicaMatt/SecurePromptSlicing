import java.util.*;  
      
    public class LoginSystem {  
        private String username;  
        private String email;  
        private String password;  
          
        public LoginSystem(String username, String email, String password) {  
            this.username = username;  
            this.email = email;  
            this.password = password;  
        }  
          
        public boolean isLoggedIn() {  
            return true;  
        }  
      
        public String getEmail() {  
            return email;  
        }  
      
        public void setEmail(String newEmail) {  
            this.email = newEmail;  
        }  
    }