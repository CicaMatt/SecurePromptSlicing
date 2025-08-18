import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribeChecker {

    public static void main(String[] args) {
        int result = checkAndUnsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        if (!emailExists(email)) {
            return 0;
        }
        return unsubscribeEmail(email) ? 1 : 0;
    }

    private static boolean emailExists(String email) {
        // This method should contain logic to check if the email exists.
        // For demonstration purposes, let's assume it always returns true.
        return true;
    }

    private static boolean unsubscribeEmail(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script.sh", email);
            Process process = processBuilder.start();
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