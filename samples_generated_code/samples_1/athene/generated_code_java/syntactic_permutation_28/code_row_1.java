import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect");

    public String getRedirectTarget(String targetURL) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetURL);
        if (matcher.matches()) {
            return targetURL;
        }
        return null;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/redirect";
        String redirectTarget = handler.getRedirectTarget(targetURL);
        System.out.println(redirectTarget != null ? redirectTarget : "No match");
    }
}