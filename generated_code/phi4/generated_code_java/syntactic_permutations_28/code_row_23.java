import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final Pattern PATTERN = Pattern.compile("your-regex-here");

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl; // Use the target URL as redirect target
        }
        return null; // No redirection needed
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/target-path";
        String testUrl2 = "http://another-example.com/other-path";

        if (getRedirectUrl(testUrl1) != null) {
            System.out.println("Redirecting to: " + testUrl1);
        } else {
            System.out.println("No redirect for: " + testUrl1);
        }

        if (getRedirectUrl(testUrl2) != null) {
            System.out.println("Redirecting to: " + testUrl2);
        } else {
            System.out.println("No redirect for: " + testUrl2);
        }
    }
}
