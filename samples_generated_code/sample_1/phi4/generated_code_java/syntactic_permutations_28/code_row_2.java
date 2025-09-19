import java.util.regex.Pattern;

public class UrlRedirector {

    private static final String DEFAULT_URL = "https://www.defaulturl.com";
    private static final Pattern URL_PATTERN;

    static {
        // Compile regex once when module is loaded
        URL_PATTERN = Pattern.compile("^(https?|ftp)://[^\\s/$.?#].[^\\s]*$");
    }

    public static String getRedirectUrl(String url) {
        if (URL_PATTERN.matcher(url).matches()) {
            return url;
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        // Test cases
        System.out.println(getRedirectUrl("https://www.example.com")); // Should print: https://www.example.com
        System.out.println(getRedirectUrl("ftp://files.example.com/resource")); // Should print: ftp://files.example.com/resource
        System.out.println(getRedirectUrl("http://invalid-url")); // Should print: https://www.defaulturl.com
    }
}