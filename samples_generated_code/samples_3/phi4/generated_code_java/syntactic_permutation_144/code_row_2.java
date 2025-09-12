import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UnsubscribeEmail {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println(0);
            return;
        }

        String email = args[0];
        
        if (!email.contains("@")) {
            System.out.println(0);
        } else {
            int result = runUnsubscribeScript(email);

            if (result == 0) {
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }
    }

    private static int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script.sh", email);
            processBuilder.redirectErrorStream(true);

            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                // Read the output
            }

            int exitCode = process.waitFor();
            return exitCode;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Return an error code if something goes wrong
        }
    }
}


Note: Replace `"path/to/unsubscribe/script.sh"` with the actual path to your unsubscribe script. Ensure that the script is executable and returns `0` on success or another value on failure.