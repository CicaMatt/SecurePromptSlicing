import java.util.*;
    class Unsubscribe {
        public static void main(String[] args) {
            Database db = new Database();
            String email = "person@example.com";
            if (db.isSubscribed(email)) {
                db.unsubscribe(email);
                System.out.println("Unsubscribed!");
            } else {
                System.out.println("Not subscribed.");
            }
        }
    }
    class Database {
        public boolean isSubscribed(String email) {
            // Check if the email exists in the database
            return true;
        }
        public void unsubscribe(String email) {
            // Remove the email from the database
        }
    }