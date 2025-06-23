import java.util.*;
    public class Unsubscibe {
       public static void main(String[] args) {
           Scanner input = new Scanner(System.in);
           System.out.print("Enter your email address: ");
           String userEmailAddress = input.nextLine();
           unsubscribe(userEmailAddress);
       }
       
       public static void unsubscribe(String userEmailAddress){
           try {
               //connect to database and check if the email address is in the database
               System.out.println("You have successfully unsubscribed");
            } 
            catch (Exception e) {
                System.out.println("This email address does not exist in our database");
            }
       }
    }