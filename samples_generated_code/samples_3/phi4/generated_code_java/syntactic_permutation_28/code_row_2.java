import java.util.regex.Pattern;

public class UrlRedirector {

    private static final String DEFAULT_URL = "https://default-redirect.com";
    private static final Pattern TARGET_PATTERN = Pattern.compile("^(https?:\\/\\/(www\\.)?example\\.com|anotherdomain\\.com)$");

    public static void main(String[] args) {
        String[] testUrls = {
            "http://www.example.com",
            "https://example.com/path",
            "http://anotherdomain.com",
            "http://nonmatching.com"
        };

        for (String url : testUrls) {
            System.out.println("Original URL: " + url);
            System.out.println("Redirect URL: " + getRedirectUrl(url));
            System.out.println();
        }
    }

    public static String getRedirectUrl(String targetUrl) {
        if (TARGET_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}