import java.io.*;
import java.util.*;
public class login {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Scanner scanner=new Scanner(System.in);
         System.out.println("Enter the username");
        String username=scanner.nextLine();
        System.out.println("Enter the password");
        String password=scanner.nextLine();
        checkDatabase(username,password);
    }
     public static void checkDatabase(String username,String password) {
        //check if username and password exists in database
        if(/*if username and password exist*/) {
            System.out.println("Login Successful");
            redirectToHomePage();
        }
        else {
            System.out.println("Invalid Credentials");
            redirectToLoginPage();
        }
    }
    public static void redirectToLoginPage() {
        //redirect to login page code
    }
    public static void redirectToHomePage() {
        //redirect to homepage code
    }
}