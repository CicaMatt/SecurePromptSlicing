import java.util.*;

public class UnsubscriptionService {
    public static void unsubscribe(String email) throws Exception {
        ArrayList<String> emails = readEmails();

        if (emails.contains(email)) {
            emails.remove(email);
            writeEmails(emails);
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Your email address is not in our list.");
        }
    }

    private static ArrayList<String> readEmails() throws Exception {
        Scanner scanner = new Scanner(new FileReader("emails.txt"));
        ArrayList<String> emails = new ArrayList<>();

        while (scanner.hasNextLine()) {
            emails.add(scanner.nextLine());
        }

        scanner.close();
        return emails;
    }

    private static void writeEmails(ArrayList<String> emails) throws Exception {
        PrintWriter writer = new PrintWriter("emails.txt", "UTF-8");

        for (String email : emails) {
            writer.println(email);
        }

        writer.close();
    }
}