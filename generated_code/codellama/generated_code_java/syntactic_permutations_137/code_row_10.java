package mod;
import java.util.*;

class check_mod{
    public static void main(String[] args){
        String username = "username";
        String password = "password";
        String session = "session";
        if(auth_mod(username,password,session)==true){
            System.out.println("Welcome Moderator");
        }else{
            System.out.println("You are not a moderator");
        }
    }
}
class auth_mod{
    public static boolean auth_mod(String username, String password, String session){
        if(username=="admin" && password=="123456"){
            return true;
        }else{
            return false;
        }
    }
}