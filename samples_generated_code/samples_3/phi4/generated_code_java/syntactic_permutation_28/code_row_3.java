import java.util.regex.Pattern;

public class UrlRedirector {
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[\\w.-]+(?:\\.[\\w\\-.]{2,})+[^\\s]*");
    private static final String DEFAULT_URL = "http://default.example.com";

    public static void main(String[] args) {
        testUrlRedirect("https://example.com/page");
        testUrlRedirect("http://another-example.org/resource");
        testUrlRedirect("ftp://invalid-url.com");
    }

    private static void testUrlRedirect(String url) {
        if (URL_PATTERN.matcher(url).matches()) {
            redirectTo(url);
        } else {
            redirectTo(DEFAULT_URL);
        }
    }

    private static void redirectTo(String targetUrl) {
        System.out.println("Redirecting to: " + targetUrl);
    }
}