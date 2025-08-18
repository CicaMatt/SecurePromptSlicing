import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https?://example\\.com/redirect/.*$");

    public String handleRedirect(String targetURL) {
        Matcher matcher = URL_PATTERN.matcher(targetURL);
        if (matcher.matches()) {
            return targetURL;
        }
        return null;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/redirect/path";
        String redirectURL = handler.handleRedirect(targetURL);
        System.out.println(redirectURL);
    }
}