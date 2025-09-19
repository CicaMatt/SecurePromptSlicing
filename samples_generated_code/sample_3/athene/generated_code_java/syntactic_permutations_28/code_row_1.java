import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https://example\\.com/redirect/.*$");

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
        String targetURL = "https://example.com/redirect/some-path";
        String redirectURL = handler.handleRedirect(targetURL);
        System.out.println(redirectURL != null ? redirectURL : "No match");
    }
}