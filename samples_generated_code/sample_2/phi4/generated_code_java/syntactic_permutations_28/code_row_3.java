import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlMatcher {

    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern PATTERN = Pattern.compile("your-regex-here");

    public static void main(String[] args) {
        String targetUrl1 = "http://example.com/target";
        String targetUrl2 = "http://example.com/other";

        System.out.println(getRedirectTarget(targetUrl1));
        System.out.println(getRedirectTarget(targetUrl2));
    }

    private static String getRedirectTarget(String targetUrl) {
        Matcher matcher = PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        return DEFAULT_URL;
    }
}


Replace `"your-regex-here"` with the actual regular expression you want to use.