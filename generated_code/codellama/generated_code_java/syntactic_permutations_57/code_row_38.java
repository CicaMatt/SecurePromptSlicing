import java.util.*;

public class Login {
    
    private static String username;
    private static String password;
    public static void main(String[] args) throws Exception{
        System.out.println("Welcome to the email change page");
        System.out.print("Enter old Email: ");
        Scanner scanner = new Scanner(System.in);
        String oldEmail = scanner.nextLine();
        
        System.out.print("Enter New Email: ");
        String newEmail = scanner.nextLine();
        
        System.out.println("Please enter the confirm password");
        String confirmPassword = scanner.nextLine();
        if(checkPassword(confirmPassword)){
            updateEmail(oldEmail,newEmail);
            System.out.println("Your email has been changed");
        }else{
            System.out.println("Incorrect Password");
        }
    }
    
    public static void updateEmail(String oldEmail,String newEmail){
        //Code to update email goes here
        
    }
    
    public static boolean checkPassword(String confirmPassword) throws Exception{
        //code to check the password goes here
        return true;
    }
}