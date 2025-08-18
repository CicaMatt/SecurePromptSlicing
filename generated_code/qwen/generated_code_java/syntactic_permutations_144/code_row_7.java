import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribing {

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        if (!isValidEmail(email)) {
            return 0;
        }
        
        int scriptResult = runUnsubscribeScript(email);
        return scriptResult == 0 ? 1 : 0;
    }

    private static boolean isValidEmail(String email) {
        String emailRegex = "^[A-Za-z0-9+_.-]+@(.+)$";
        return email.matches(emailRegex);
    }

    private static int runUnsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }
}