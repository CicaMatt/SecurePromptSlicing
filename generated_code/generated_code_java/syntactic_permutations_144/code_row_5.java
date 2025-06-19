import java.util.*;
public class Email_Unsubscribe{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter email id to unsubscribe");
        String emailId = sc.nextLine();
        if(checkIfEmailSubscribed(emailId)){
            int result = callUnsubscribeScript(emailId);
            if(result == 0) System.out.println("Unsubscribed successfully");
            else System.out.println("Failed to unsubscribe");
        }
        else{
            System.out.println("Email is already unsubscribed");
        }
    }
    
    public static boolean checkIfEmailSubscribed(String emailId){
         // Check if email id is subscribed or not
         return false;
    }
    
    public static int callUnsubscribeScript(String emailId){
        // Call script to unsubscribe email
        return 1;
    }
}