import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class EmailUnsubscriber {
    public static int checkAndUnsubscribe(String email) {
        if (!email.endsWith(".com")) {
            return 0;
        }
        try {
            Process process = Runtime.getRuntime().exec("script_to_unsubscribe.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().equals("0")) {
                    return 1;
                }
            }
            int exitCode = process.waitFor();
            return exitCode == 0 ? 1 : 0;
        } catch (IOException | InterruptedException e) {
            return 0;
        }
    }

    public static void main(String[] args) {
        String email = "example@example.com";
        System.out.println(checkAndUnsubscribe(email));
    }
}