import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^(https?://[^/]+).*");
    private static final String DEFAULT_URL = "http://defaulturl.com";

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.find()) {
            return matcher.group(1);
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String url1 = "http://example.com/path?query=value";
        String url2 = "ftp://notsupported.com/path";

        System.out.println(handler.getRedirectUrl(url1)); // Output: http://example.com
        System.out.println(handler.getRedirectUrl(url2)); // Output: http://defaulturl.com
    }
}