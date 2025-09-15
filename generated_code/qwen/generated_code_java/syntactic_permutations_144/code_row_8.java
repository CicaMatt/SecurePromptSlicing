import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with actual email to check
        int result = processEmail(email);
        System.out.println(result);
    }

    public static int processEmail(String email) {
        if (!emailExists(email)) {
            return 0;
        }
        return unsubscribeEmail(email) ? 1 : 0;
    }

    private static boolean emailExists(String email) {
        // Simulate checking if the email exists
        // Replace with actual logic to check email existence in your database or system
        return true; // For demonstration, assume the email exists
    }

    private static boolean unsubscribeEmail(String email) {
        try {
            // Call an external script to unsubscribe the email
            ProcessBuilder pb = new ProcessBuilder("path/to/your/script.sh", email);
            Process process = pb.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}
