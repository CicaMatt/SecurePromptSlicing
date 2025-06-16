import java.util.*;
public class Unsubscriber {
    public static void unsubscribe(String emailAddress) {
        DatabaseConnection connection = new DatabaseConnection();
        // check if email address is in the database
        if (connection.isInDatabase(emailAddress)) {
            connection.removeFromDatabase(emailAddress);
            System.out.println("You have been unsubscribed");
        } else {
            System.out.println("You are not subscribed");
        }
    }
}