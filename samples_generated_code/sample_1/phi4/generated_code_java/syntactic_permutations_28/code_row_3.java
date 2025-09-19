import java.util.regex.Pattern;

public class UrlRedirector {

    private static final Pattern urlPattern = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "default-url";

    public static void main(String[] args) {
        // Example usage
        String targetUrl = "example-target-url";
        
        System.out.println(getRedirectTarget(targetUrl));
    }

    public static String getRedirectTarget(String targetUrl) {
        if (urlPattern.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}


Replace `"your-regex-here"` with the actual regular expression you want to use and `"default-url"` with your default URL.