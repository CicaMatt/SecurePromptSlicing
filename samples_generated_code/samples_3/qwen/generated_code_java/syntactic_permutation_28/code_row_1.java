import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect/(.*)$");

    public static void main(String[] args) {
        String targetURL = "http://example.com/redirect/newpage";
        String redirectTarget = getRedirectTarget(targetURL);
        
        if (redirectTarget != null) {
            System.out.println("Redirecting to: " + redirectTarget);
        } else {
            System.out.println("No redirection needed.");
        }
    }

    public static String getRedirectTarget(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        if (matcher.matches()) {
            return matcher.group(1); // Use the matched group as the redirect target
        }
        return null;
    }
}