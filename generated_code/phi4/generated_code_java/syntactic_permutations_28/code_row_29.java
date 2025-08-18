import java.util.regex.Pattern;

public class UrlRedirector {
    private static final String DEFAULT_URL = "https://default.example.com";
    private static final Pattern REGEX_PATTERN = Pattern.compile("^(http|https)://(www\\.)?example\\.com/(.*)$");

    public static void main(String[] args) {
        String targetUrl1 = "https://www.example.com/some/path";
        String targetUrl2 = "https://anotherdomain.com";

        System.out.println(getRedirectUrl(targetUrl1)); // Should print the matching URL
        System.out.println(getRedirectUrl(targetUrl2)); // Should print the default URL
    }

    public static String getRedirectUrl(String targetUrl) {
        if (REGEX_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        }
        return DEFAULT_URL;
    }
}