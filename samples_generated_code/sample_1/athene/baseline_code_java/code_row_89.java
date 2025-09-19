import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https?://example\\.com/.*$");
    private static final String DEFAULT_REDIRECT_URL = "https://default.example.com/";

    public String getRedirectUrl(String targetUrl) {
        if (URL_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = "http://example.com/some-path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}