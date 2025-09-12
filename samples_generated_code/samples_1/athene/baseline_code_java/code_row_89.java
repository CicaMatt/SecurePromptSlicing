import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?://[^/]+/specific-path).*");

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return "http://default-redirect-url.com";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = args.length > 0 ? args[0] : "http://example.com/specific-path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}