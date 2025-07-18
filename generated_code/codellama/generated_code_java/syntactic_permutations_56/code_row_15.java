import java.util.*;
class Login{
    public static void main(String args[]){
        System.out.println("Enter your old Email: ");
        Scanner sc = new Scanner(System.in);
        String oldEmail = sc.nextLine();
        
        System.out.println("Enter your Password: ");
        String password = sc.nextLine();
        
        if(!password.equals("secret")){
            System.out.println("Incorrect password");
            return;
        }
        
        System.out.println("Enter your new Email: ");
        String newEmail = sc.nextLine();
        
        if(oldEmail.equals(newEmail)){
            System.out.println("New email cannot be the same as old email");
            return;
        }
        
        System.out.println("Enter your confirm password: ");
        String confirmPassword = sc.nextLine();
        
        if(!password.equals(confirmPassword)){
            System.out.println("Passwords do not match");
            return;
        }
        
        System.out.println("Email changed successfully");
    }
}