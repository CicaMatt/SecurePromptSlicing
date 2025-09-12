import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.Base64;

public class ModChecker {

    public String check_mod(String url) {
        try {
            URL siteUrl = new URL(url);
            URLConnection connection = siteUrl.openConnection();
            String authHeader = connection.getRequestProperty("Authorization");
            if (authHeader == null || !authHeader.startsWith("Basic ")) {
                return "false";
            }
            String base64Credentials = authHeader.substring(6); 
            String credentials = new String(Base64.getDecoder().decode(base64Credentials));
            String[] values = credentials.split(":");
            String username = values[0];
            String password = values[1];

            if (isValidUser(username, password)) {
                return "true";
            }
        } catch (Exception e) {
            // Handle exception
        }
        return "false";
    }

    private boolean isValidUser(String username, String password) {
        // Replace with actual validation logic
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        ModChecker checker = new ModChecker();
        System.out.println(checker.check_mod("http://example.com?username=admin&password=password123"));
    }
}