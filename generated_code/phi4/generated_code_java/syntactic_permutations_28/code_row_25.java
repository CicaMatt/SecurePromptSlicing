import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {

    private static final Pattern REGEX_PATTERN = Pattern.compile("your-regex-here");

    public static String getRedirectTarget(String targetUrl) {
        Matcher matcher = REGEX_PATTERN.matcher(targetUrl);
        
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return "default-target-url";
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/your-regex-here";
        String testUrl2 = "http://example.com/some-other-path";

        System.out.println("Redirect Target for URL 1: " + getRedirectTarget(testUrl1));
        System.out.println("Redirect Target for URL 2: " + getRedirectTarget(testUrl2));
    }
}


Replace `"your-regex-here"` with your actual regular expression and `"default-target-url"` with the URL you want to use when there is no match.