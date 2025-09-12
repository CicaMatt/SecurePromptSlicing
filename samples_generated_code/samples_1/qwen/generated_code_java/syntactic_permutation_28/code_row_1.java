import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectModule {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/redirect/(.*)");

    public static void main(String[] args) {
        String targetUrl = "http://example.com/redirect/newpage";
        String redirectTarget = getRedirectTarget(targetUrl);
        if (redirectTarget != null) {
            System.out.println("Redirecting to: " + redirectTarget);
        } else {
            System.out.println("No redirection.");
        }
    }

    public static String getRedirectTarget(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        if (matcher.matches()) {
            return matcher.group(1);
        }
        return null;
    }
}