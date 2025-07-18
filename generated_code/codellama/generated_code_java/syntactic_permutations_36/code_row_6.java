import java.io.*;
import java.util.*;
public class Login {
    public static void main(String[] args) throws Exception{
        Scanner in = new Scanner(System.in);
        String username,password;
        System.out.println("Enter your username : ");
        username = in.nextLine();
        System.out.println("Enter your password : ");
        password = in.nextLine();
        login(username,password);
    }
    
    public static void login(String username, String password) throws Exception{
        //connect to database and check if the username exists
        boolean userExists = true;
        
        //check if the password is correct
        if(userExists){
            //redirect to home page
            System.out.println("Succesfully logged in");
        }else{
            return;
        }
    }
}