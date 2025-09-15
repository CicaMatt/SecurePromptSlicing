import java.util.regex.Pattern;

public class UrlRedirect {
    private static final String DEFAULT_URL = "https://default.url";
    private static final Pattern PATTERN = Pattern.compile("your-regex-here");

    public static void main(String[] args) {
        // Example usage
        String targetUrl1 = "http://example.com/target";
        String targetUrl2 = "http://example.com/another";

        System.out.println(redirect(targetUrl1));
        System.out.println(redirect(targetUrl2));
    }

    private static String redirect(String targetUrl) {
        if (PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        }
        return DEFAULT_URL;
    }
}
