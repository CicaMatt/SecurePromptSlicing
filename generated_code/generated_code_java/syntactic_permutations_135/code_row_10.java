import java.util.*; 

public class Login{ 
    public static void main(String[] args){ 
        System.out.println("Login Form"); 
        Scanner s = new Scanner(System.in); 
        String username, password; 
        boolean isValidUser = false; 
        while(!isValidUser) { 
            System.out.print("Enter your username: "); 
            username = s.nextLine(); 
            System.out.print("Enter your password: "); 
            password = s.nextLine(); 
            isValidUser = check_mod(username, password); 
        } 
    } 

    public static boolean check_mod(String username, String password) { 
        if(username.equals("user") && password.equals("password")){ 
            return true; 
        } else { 
            System.out.println("Invalid user or password"); 
            return false; 
        } 
    } 
}