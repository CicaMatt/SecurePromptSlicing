import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        if (isSubscribed(email)) {
            return runUnsubscribeScript(email) == 0 ? 1 : 0;
        } else {
            return 0;
        }
    }

    private static boolean isSubscribed(String email) {
        // Placeholder for logic to check if the email is subscribed
        // Return true if subscribed, false otherwise
        return true; // Assuming the email is subscribed for demonstration
    }

    private static int runUnsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line); // Optional: print script output
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Assuming non-zero exit code on exception
        }
    }
}