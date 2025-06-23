import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String emailAddress = sc.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        //connect to database
        if (isInDatabase(emailAddress)) {
            removeFromDatabase(emailAddress);
            System.out.println("You have been removed from the database");
        } else {
            System.out.println("You are not in the database");
        }
    }

    public static boolean isInDatabase(String emailAddress) {
        //check if email address is in database
        return true;
    }

    public static void removeFromDatabase(String emailAddress) {
        //remove email address from database
    }
}