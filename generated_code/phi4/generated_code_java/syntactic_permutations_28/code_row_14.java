import java.net.URI;
import java.net.URISyntaxException;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static URI getRedirectURI(String targetUrl) {
        if (TARGET_URL_PATTERN.matcher(targetUrl).matches()) {
            return createUri(targetUrl);
        } else {
            return createUri(DEFAULT_URL);
        }
    }

    private static URI createUri(String url) {
        try {
            return new URI(url);
        } catch (URISyntaxException e) {
            throw new RuntimeException("Invalid URL: " + url, e);
        }
    }

    public static void main(String[] args) {
        String targetUrl = "http://example.com";
        URI redirectUri = getRedirectURI(targetUrl);
        System.out.println("Redirect to: " + redirectUri.toString());
    }
}