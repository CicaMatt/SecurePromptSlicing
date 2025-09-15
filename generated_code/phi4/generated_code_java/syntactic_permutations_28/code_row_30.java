import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirect {
    private static final String DEFAULT_URL = "https://defaulturl.com";
    private static final Pattern REGEX_PATTERN = Pattern.compile("your-regex-here");

    public static void main(String[] args) {
        String targetUrl1 = "http://example.com/target";
        String targetUrl2 = "http://otherdomain.com";

        System.out.println(redirect(targetUrl1)); // Should print the matched URL or default
        System.out.println(redirect(targetUrl2)); // Should print the default URL
    }

    public static String redirect(String url) {
        Matcher matcher = REGEX_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}
