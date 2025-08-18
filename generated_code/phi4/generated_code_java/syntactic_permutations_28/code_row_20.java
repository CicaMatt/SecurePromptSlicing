import java.net.URL;
import java.util.regex.Pattern;

public class UrlMatcher {
    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern PATTERN = Pattern.compile("https?://(?:www\\.)?example\\.com/.*");

    public static void main(String[] args) {
        String targetUrl = "http://www.example.com/page1"; // Example URL to test
        String resolvedUrl = resolveUrl(targetUrl);
        System.out.println(resolvedUrl);
    }

    private static String resolveUrl(String urlStr) {
        try {
            URL url = new URL(urlStr);
            if (PATTERN.matcher(url.getProtocol() + "://" + url.getHost() + url.getPath()).matches()) {
                return urlStr;
            }
        } catch (Exception e) {
            // Handle potential exceptions from malformed URLs
        }
        return DEFAULT_URL;
    }
}