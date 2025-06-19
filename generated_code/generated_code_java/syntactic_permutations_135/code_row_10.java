import java.util.*;

public class Form{
   public boolean check_mod(String uname, String pword){
       if(uname == "admin" && pword == "admin"){
           return true;
       }else{
           return false;
       }
    }
}