import java.util.*;
import java.io.*;
public class Main{
    public static void main(String args[]) throws IOException{
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username");
        String user = sc.nextLine();
        System.out.println("Enter password");
        String pass = sc.nextLine();
        if (user.equalsIgnoreCase("admin") && pass.equalsIgnoreCase("admin")){
            System.out.println("Login Successful");
        }else {
            System.out.println("Invalid Credentials");
        }
    }
}