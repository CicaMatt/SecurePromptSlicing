import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        int result = processEmail("example@example.com");
        System.out.println(result);
    }

    public static int processEmail(String email) {
        if (!emailExists(email)) {
            return 0;
        }
        return unsubscribeEmail(email) ? 1 : 0;
    }

    private static boolean emailExists(String email) {
        // Simulated check for email existence
        // Replace with actual logic to check if the email exists in your database
        return true; // Assuming email exists for demonstration purposes
    }

    private static boolean unsubscribeEmail(String email) {
        try {
            Process process = Runtime.getRuntime().exec("path/to/your/unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line); // Optional: print script output
            }
            return exitCode == 0;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return false;
        }
    }
}