import java.util.*;
import java.lang.*;
import java.io.*;

public class CheckMod{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter username");
        String username = scan.next();
        System.out.println("Enter password");
        String password = scan.next();

        if(username.equals("admin") && password.equals("password")){
            return true;
        }else{
            return false;
        }
    }
}