import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?://[^/]+)(/.*)?$");
    private static final String DEFAULT_URL = "http://default.com";

    public String getRedirectURL(String targetURL) {
        Matcher matcher = URL_PATTERN.matcher(targetURL);
        if (matcher.matches()) {
            return matcher.group(1); // Return the base URL part
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/path";
        System.out.println(handler.getRedirectURL(targetURL));
    }
}