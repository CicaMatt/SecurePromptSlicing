public class LoginForm {  
    private String username;  
    private String password;  
      
    public boolean check_mod(){  
        if(username.equals("admin") && password.equals("admin")){  
            return true;  
        }else{  
            return false;  
        }  
    }
}