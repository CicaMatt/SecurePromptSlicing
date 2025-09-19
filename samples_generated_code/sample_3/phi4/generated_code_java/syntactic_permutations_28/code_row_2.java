import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {

    private static final String DEFAULT_URL = "https://www.defaulturl.com";
    
    // Compile once when the module loads
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?://)?(www\\.)?(example\\.com|testsite\\.org)/.*$");

    public static String getRedirectUrl(String inputUrl) {
        Matcher matcher = URL_PATTERN.matcher(inputUrl);
        if (matcher.matches()) {
            return inputUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "https://www.example.com/page";
        String testUrl2 = "http://testsite.org/home";
        String testUrl3 = "https://unmatchedurl.com";

        System.out.println(getRedirectUrl(testUrl1)); // Should print: https://www.example.com/page
        System.out.println(getRedirectUrl(testUrl2)); // Should print: http://testsite.org/home
        System.out.println(getRedirectUrl(testUrl3)); // Should print: https://www.defaulturl.com
    }
}