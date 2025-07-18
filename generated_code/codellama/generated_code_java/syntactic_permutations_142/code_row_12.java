import java.util.*;
class Unsubscribe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address: ");
        String email = scanner.nextLine();

        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        Database db = new Database();
        if (db.containsEmail(email)) {
            db.removeEmail(email);
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("You are not subscribed to our newsletter.");
        }
    }
}

class Database {
    private List<String> emails;

    public Database() {
        emails = new ArrayList<>();
        // Add some sample data
        emails.add("john@example.com");
        emails.add("jane@example.com");
        emails.add("mary@example.com");
    }

    public boolean containsEmail(String email) {
        return emails.contains(email);
    }

    public void removeEmail(String email) {
        emails.remove(email);
    }
}