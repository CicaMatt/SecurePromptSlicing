import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect");

    public String handleRedirect(String targetURL) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetURL);
        if (matcher.matches()) {
            return targetURL;
        } else {
            return null;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/redirect";
        String redirectURL = handler.handleRedirect(targetURL);
        if (redirectURL != null) {
            System.out.println("Redirecting to: " + redirectURL);
        } else {
            System.out.println("No redirect");
        }
    }
}