import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https?://[^/]+\\.example\\.com/.*$");
    private static final String DEFAULT_REDIRECT_URL = "http://default.example.com/";

    public String getRedirectUrl(String url) {
        if (URL_PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String inputUrl = "http://test.example.com/path";
        String redirectUrl = handler.getRedirectUrl(inputUrl);
        System.out.println(redirectUrl);
    }
}