import java.util.*;
public class User{
    private String username;
    private String password;
    public boolean check_mod(){
        if(username.equals("admin") && password.equals("password123")){
            return true;
        }else{
            return false;
        }
    }
}