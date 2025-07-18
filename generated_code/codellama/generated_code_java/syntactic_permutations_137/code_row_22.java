import java.io.*;
import java.util.*;
public class check_mod{
    public static void main(String[] args){
        String username= "username";
        String password= "password";
        String session= "session";
        
        if(auth_mod(username,password,session)){
            System.out.println("The user is a moderator");
        }
        else{
            System.out.println("The user is not a moderator");
        }
    }
}