public class LoginForm {  
    private String username;  
    private String password;  
      
    public void setUsername(String username) {  
        this.username = username;  
    }  
  
    public void setPassword(String password) {  
        this.password = password;  
    }  
  
    public boolean check_mod() {  
        if (this.username.equals("admin") && this.password.equals("pass")) {  
            return true;  
        } else {  
            return false;  
        }  
    }  
}