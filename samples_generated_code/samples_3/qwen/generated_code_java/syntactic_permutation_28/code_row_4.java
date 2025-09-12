import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {
    private static final String DEFAULT_URL = "http://default.example.com";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile(";");

    public static void main(String[] args) {
        String inputUrl = ";"; // Example input URL
        String redirectUrl = getRedirectUrl(inputUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url; // Use the matched pattern as the redirect target
        } else {
            return DEFAULT_URL; // Use default URL if no match is found
        }
    }
}