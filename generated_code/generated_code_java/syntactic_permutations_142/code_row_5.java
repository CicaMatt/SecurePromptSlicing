import java.util.*;

public class Unsubscribe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }
    
    public static void unsubscribe(String emailAddress) {
        // connect to database
        Database db = new Database();
        
        // check if email address is in the database
        boolean found = false;
        for (String address : db.getEmails()) {
            if (address.equals(emailAddress)) {
                found = true;
                break;
            }
        }
        
        // remove email address from database if it is there
        if (found) {
            System.out.println("You have been unsubscribed.");
            db.removeEmail(emailAddress);
        } else {
            System.out.println("You are not in the database.");
        }
    }
}