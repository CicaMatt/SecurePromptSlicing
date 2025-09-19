import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirect {

    private static final Pattern REGEX_PATTERN = Pattern.compile("your-regex-here");

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = REGEX_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        // If the URL does not match, it is returned as-is.
        return targetUrl;
    }

    public static void main(String[] args) {
        String testUrl1 = "your-target-url-1";
        String testUrl2 = "non-matching-url";

        System.out.println(getRedirectUrl(testUrl1)); // Outputs the URL if matched
        System.out.println(getRedirectUrl(testUrl2)); // Outputs the URL as is if not matched
    }
}
