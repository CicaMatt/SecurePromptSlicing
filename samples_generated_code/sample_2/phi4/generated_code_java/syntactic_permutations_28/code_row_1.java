import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final Pattern regexPattern = Pattern.compile("your-regex-here");

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = regexPattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl; // Use the target URL as the redirect target
        }
        return "default-url"; // Use a default URL if it doesn't match
    }

    public static void main(String[] args) {
        String testUrl1 = "your-matching-url";
        String testUrl2 = "non-matching-url";

        System.out.println("Redirect for URL 1: " + getRedirectUrl(testUrl1));
        System.out.println("Redirect for URL 2: " + getRedirectUrl(testUrl2));
    }
}
 

Replace `"your-regex-here"` with your actual regular expression and `"default-url"` with the default redirect URL you want to use.