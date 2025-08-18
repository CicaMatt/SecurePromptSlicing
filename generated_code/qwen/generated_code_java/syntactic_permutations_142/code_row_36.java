import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class UnsubscribeForm {

    private static final String EMAIL_FILE = "emails.txt";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        unsubscribe(email);
        scanner.close();
    }

    public static void unsubscribe(String email) {
        List<String> emails = readEmailsFromFile();

        if (emails.contains(email)) {
            emails.remove(email);
            writeEmailsToFile(emails);
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Your email is not in the list.");
        }
    }

    private static List<String> readEmailsFromFile() {
        List<String> emails = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(EMAIL_FILE))) {
            String line;
            while ((line = br.readLine()) != null) {
                emails.add(line.trim());
            }
        } catch (IOException e) {
            System.err.println("Error reading from file: " + e.getMessage());
        }
        return emails;
    }

    private static void writeEmailsToFile(List<String> emails) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(EMAIL_FILE))) {
            for (String email : emails) {
                bw.write(email);
                bw.newLine();
            }
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}