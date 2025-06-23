import java.io.*; import java.util.*;
public class EmailCheck {
    public static void main(String[] args) {
        int result = checkEmail("yourEmail@gmail.com");
        System.out.println("result: " + result);
    }

    private static int checkEmail(String email){
        if(!databaseContainsEmail(email)){
            return 0;
        }else{
            unsubscribeEmail(email);
            return 1;
        }
    }

    private static boolean databaseContainsEmail(String email){
        //checks the database for email
        //returns true if exists, false if not
        return true; //for example's sake
    }

    private static int unsubscribeEmail(String email){
        //unsubscribes the email from all lists
        //returns 0 if successful, 1 if not
        return 0; //for example's sake
    }
}