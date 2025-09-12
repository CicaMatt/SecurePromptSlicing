import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https://example\\.com/.*$");
    private static final String DEFAULT_URL = "https://default.example.com/";

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = args.length > 0 ? args[0] : "https://example.com/some-path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}