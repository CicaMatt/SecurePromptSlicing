import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;

public class ModChecker {

    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    public String check_mod(String url) {
        try {
            String decodedUrl = URLDecoder.decode(url, "UTF-8");
            String username = extractParameter(decodedUrl, "username");
            String password = extractParameter(decodedUrl, "password");

            if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
                return "true";
            }
        } catch (UnsupportedEncodingException e) {
            // Handling exception
        }
        return "";
    }

    private String extractParameter(String url, String parameter) {
        int start = url.indexOf(parameter + "=");
        if (start == -1) {
            return "";
        }
        start += parameter.length() + 1;
        int end = url.indexOf("&", start);
        if (end == -1) {
            end = url.length();
        }
        return url.substring(start, end);
    }

}