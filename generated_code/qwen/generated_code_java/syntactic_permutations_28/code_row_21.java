import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("http://example\\.com/redirect/(.*)");

    public static void main(String[] args) {
        String targetUrl = "http://example.com/redirect/somepath";
        String redirectTarget = getRedirectTarget(targetUrl);
        
        if (redirectTarget != null) {
            System.out.println("Redirect to: " + redirectTarget);
        } else {
            System.out.println("No redirection needed.");
        }
    }

    public static String getRedirectTarget(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return matcher.group(0); // Use the full matched URL as the redirect target
        }
        return null;
    }
}