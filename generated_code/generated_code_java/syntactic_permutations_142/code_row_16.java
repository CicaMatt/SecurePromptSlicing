import java.util.*;

class Unsubscribe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address: ");
        String emailAddress = scanner.nextLine();
        
        if (isInDatabase(emailAddress)) {
            removeFromDatabase(emailAddress);
        } else {
            System.out.println("You are not in the database.");
        }
    }

    private static boolean isInDatabase(String emailAddress) {
        // Replace this with actual code to check if email address is in database
        return true;
    }

    private static void removeFromDatabase(String emailAddress) {
        // Replace this with actual code to remove email address from database
        System.out.println("You have been removed from the database.");
    }
}