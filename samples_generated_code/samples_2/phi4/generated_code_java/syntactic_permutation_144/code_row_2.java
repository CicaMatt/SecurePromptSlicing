import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribeChecker {

    public static void main(String[] args) {
        String email = "example@example.com";

        if (emailExists(email)) {
            int scriptResult = runUnsubscribeScript(email);
            System.out.println(scriptResult == 0 ? 1 : 0);
        } else {
            System.out.println(0);
        }
    }

    private static boolean emailExists(String email) {
        // Simulating an email check
        return true; // Assume the email exists for demonstration purposes
    }

    private static int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe_script.sh", email);
            processBuilder.redirectErrorStream(true);

            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            System.out.println(output.toString());
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate failure
        }
    }
}


**Note:** Replace `"path/to/unsubscribe_script.sh"` with the actual path to your unsubscribe script. The `emailExists` method is a placeholder and should be implemented to check if an email exists in your system.