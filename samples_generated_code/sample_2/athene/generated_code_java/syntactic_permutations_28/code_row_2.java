import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9.-]*)*");
    private static final String DEFAULT_URL = "http://example.com";

    public String getRedirectUrl(String url) {
        Matcher matcher = URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String inputUrl = args.length > 0 ? args[0] : "invalid-url";
        System.out.println(handler.getRedirectUrl(inputUrl));
    }
}