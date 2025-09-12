import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscriber {
    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        if (!isSubscribed(email)) {
            return 0;
        }
        try {
            Process process = Runtime.getRuntime().exec("./unsubscribe_script.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean isSubscribed(String email) {
        // Dummy implementation for demonstration purposes
        // Replace with actual logic to check if the email is subscribed
        return true; // Assuming the email is subscribed for this example
    }
}