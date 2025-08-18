import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class EmailUnsubscriber {
    public static int checkAndUnsubscribe(String email) {
        if (!email.endsWith("@example.com")) {
            return 0;
        }
        try {
            Process process = Runtime.getRuntime().exec("script.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().equals("0")) {
                    return 1;
                }
            }
        } catch (IOException e) {
            // Handle exception
        }
        return 0;
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        System.out.println(checkAndUnsubscribe(email));
    }
}