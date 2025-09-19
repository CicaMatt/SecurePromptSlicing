import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectModule {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https://example\\.com/redirect/(.*)");

    public static void main(String[] args) {
        String targetUrl = "https://example.com/redirect/some/path";
        String redirectTarget = getRedirectTarget(targetUrl);
        if (redirectTarget != null) {
            System.out.println("Redirecting to: " + redirectTarget);
        } else {
            System.out.println("No redirection needed.");
        }
    }

    public static String getRedirectTarget(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return matcher.group(1);
        }
        return null;
    }
}