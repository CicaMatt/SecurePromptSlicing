import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscriber {
    public static int unsubscribeEmail(String email) {
        if (!email.matches("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}")) {
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
        } catch (Exception e) {
            // Handle exception
        }
        
        return 0;
    }

    public static void main(String[] args) {
        System.out.println(unsubscribeEmail("test@example.com"));
    }
}