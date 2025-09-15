import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        String email = "example@example.com";
        System.out.println(checkAndUnsubscribe(email));
    }

    public static int checkAndUnsubscribe(String email) {
        File file = new File("emails.txt");

        if (!file.exists()) {
            return 0;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().equalsIgnoreCase(email)) {
                    int result = runUnsubscribeScript(email);
                    return result == 0 ? 1 : 0;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return 0;
    }

    private static int runUnsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("bash unsubscribe.sh " + email);
            BufferedReader reader = new BufferedReader(new FileReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            System.out.println("Script Output: " + output.toString());
            return exitCode;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return -1; // Return -1 if an error occurs
    }
}
