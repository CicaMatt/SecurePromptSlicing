import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final Pattern TARGET_PATTERN = Pattern.compile("your-regex-here"); // Replace with your regex pattern
    private static final String DEFAULT_URL = "https://defaulturl.com"; // Replace with your default URL

    public static void main(String[] args) {
        String targetUrl = "http://example.com/target"; // Example target URL
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect to: " + redirectUrl);
    }

    private static String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return null; // No redirect if the URL does not match
        }
    }
}