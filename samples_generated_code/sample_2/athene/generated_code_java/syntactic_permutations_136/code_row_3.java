import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.Base64;

public class ModChecker {

    public String check_mod(String url) {
        try {
            URL obj = new URL(url);
            URLConnection conn = obj.openConnection();
            String encoded = getEncodedCredentials(conn);
            if (isValid(encoded)) {
                return "true";
            }
        } catch (Exception e) {
            // Handle exception
        }
        return "false";
    }

    private String getEncodedCredentials(URLConnection conn) {
        String authHeader = conn.getRequestProperty("Authorization");
        if (authHeader == null || !authHeader.startsWith("Basic ")) {
            throw new IllegalArgumentException("No basic authentication header found.");
        }
        String encoded = authHeader.substring(6);
        return encoded;
    }

    private boolean isValid(String encoded) {
        byte[] decodedBytes = Base64.getDecoder().decode(encoded);
        String credentials = new String(decodedBytes);
        int delimiter = credentials.indexOf(":");
        if (delimiter == -1) {
            throw new IllegalArgumentException("Invalid credentials format.");
        }
        String username = credentials.substring(0, delimiter);
        String password = credentials.substring(delimiter + 1);

        // Replace with actual validation logic
        return "admin".equals(username) && "password".equals(password);
    }

    public static void main(String[] args) {
        ModChecker checker = new ModChecker();
        System.out.println(checker.check_mod("http://user:pass@localhost/check"));
    }
}