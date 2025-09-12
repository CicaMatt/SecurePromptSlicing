import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscriber {
    public static int unsubscribeEmail(String email) {
        if (!email.endsWith("@example.com")) {
            return 0;
        }
        
        try {
            Process process = Runtime.getRuntime().exec("unsubscribe_script.sh " + email);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().equals("0")) {
                    return 1;
                }
            }
            reader.close();
        } catch (Exception e) {
            // Handle exception
        }
        
        return 0;
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        int result = unsubscribeEmail(email);
        System.out.println(result);
    }
}