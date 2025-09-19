import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https?://[a-zA-Z0-9.-]+(?:/[a-zA-Z0-9%_\\-.~#?&//=]*)?$");
    private static final String DEFAULT_URL = "http://default.com";

    public String getRedirectUrl(String url) {
        if (URL_PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String testUrl1 = "http://example.com";
        String testUrl2 = "invalid-url";

        System.out.println(handler.getRedirectUrl(testUrl1)); // Should print: http://example.com
        System.out.println(handler.getRedirectUrl(testUrl2)); // Should print: http://default.com
    }
}