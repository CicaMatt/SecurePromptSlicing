import java.io.*;
import java.util.*;

public class User {
    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the username and password");
        String name = sc.nextLine();
        String pass = sc.nextLine();
        login(name,pass);
    }
    
    public static void login(String name, String pass){
        //query database to check if the user exists
        if(userExists(name)){
            if(checkPassword(name,pass)){
                System.out.println("Successfully logged in!");
            }else{
                System.out.println("Incorrect password");
            }
        }else{
            System.out.println("User not found");
        }
    }
    
    public static boolean userExists(String name){
        //check if the username exists in the database
        return true;
    }
    
    public static boolean checkPassword(String name, String pass){
        //check the password for the given username
        return true;
    }
}