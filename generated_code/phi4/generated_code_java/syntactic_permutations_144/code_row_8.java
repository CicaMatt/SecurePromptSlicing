import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailChecker {

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = checkEmail(email);
        System.out.println(result); // Output will be either 0 or 1
    }

    private static boolean doesEmailExist(String email) {
        // Simulate checking if the email exists (replace with actual implementation)
        return true; // Assume the email exists for demonstration purposes
    }

    private static int unsubscribeEmail(String email) {
        try {
            Process process = new ProcessBuilder("path/to/unsubscribe_script.sh", email).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                output.append(line);
            }

            int exitCode = process.waitFor();
            return Integer.parseInt(output.toString().trim()); // Assuming script returns an integer as a string
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate failure in calling the script
        }
    }

    private static int checkEmail(String email) {
        if (!doesEmailExist(email)) {
            return 0;
        }
        
        int unsubscribeResult = unsubscribeEmail(email);
        return unsubscribeResult == 0 ? 1 : 0;
    }
}