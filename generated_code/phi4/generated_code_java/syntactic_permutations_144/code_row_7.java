import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = checkAndUnsubscribe(email);
        System.out.println(result);
    }

    public static int checkAndUnsubscribe(String email) {
        if (email == null || !email.contains("@")) {
            return 0;
        }
        
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe-script.sh " + email);
            int exitCode = process.waitFor();
            
            if (exitCode == 0) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
            return 0;
        }
    }
}
