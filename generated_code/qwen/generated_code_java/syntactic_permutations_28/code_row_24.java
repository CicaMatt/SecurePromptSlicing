import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectURLMatcher {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public static void main(String[] args) {
        String targetUrl = "http://example.com/some/path";
        String redirectTarget = getRedirectTarget(targetUrl);
        if (redirectTarget != null) {
            System.out.println("Redirecting to: " + redirectTarget);
        } else {
            System.out.println("No redirection.");
        }
    }

    public static String getRedirectTarget(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        return null;
    }
}