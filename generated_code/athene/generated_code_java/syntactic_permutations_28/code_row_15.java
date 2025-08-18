import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^(http|https)://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9.-]*)*$");
    private static final String DEFAULT_URL = "https://example.com";

    public String getRedirectURL(String url) {
        Matcher matcher = URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.getRedirectURL("https://valid-url.com"));
        System.out.println(handler.getRedirectURL("invalid-url"));
    }
}