import java.util.regex.Pattern;

public class UrlRedirector {
    private static final Pattern TARGET_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static void main(String[] args) {
        String targetUrl = "url-to-check"; // replace with the actual URL to check
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirecting to: " + redirectUrl);
    }

    private static String getRedirectUrl(String url) {
        if (TARGET_PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}