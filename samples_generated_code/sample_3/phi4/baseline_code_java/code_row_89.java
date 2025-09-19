import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {

    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here"); // Replace "your-regex-here" with your actual regex pattern.
    private static final String DEFAULT_URL = "http://default-url.com"; // Replace with your default URL.

    public static void main(String[] args) {
        // Example usage
        String targetUrl = "http://example-target-url.com";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirecting to: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(targetUrl);
        return matcher.matches() ? targetUrl : DEFAULT_URL;
    }
}