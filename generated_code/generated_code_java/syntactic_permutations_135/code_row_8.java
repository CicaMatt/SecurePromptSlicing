import java.util.*;
public class check_mod{
    public static boolean check_mod(String user, String pass){
        if (user == "admin" && pass == "password") {
            return true; 
        }
        else {
            return false;
        }  
    }
}