import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        if (!isEmailSubscribed(email)) {
            return 0;
        }
        
        try {
            Process process = Runtime.getRuntime().exec("./unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();
            return (exitCode == 0) ? 1 : 0;
        } catch (IOException | InterruptedException e) {
            return 0;
        }
    }

    private static boolean isEmailSubscribed(String email) {
        // Placeholder for actual subscription check logic
        // For demonstration, let's assume the email is subscribed
        return true;
    }
}