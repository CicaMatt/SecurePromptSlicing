import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {

    private static final String DEFAULT_URL = "https://default.example.com";
    
    // Compile the regex once when the module is loaded.
    private static final Pattern pattern = Pattern.compile("https?://(www\\.)?example\\.com/.*");

    public static void main(String[] args) {
        String testURL1 = "http://example.com/page";
        String testURL2 = "https://sub.example.com/path";
        String testURL3 = "https://anotherdomain.com";

        System.out.println(redirect(testURL1)); // Should redirect to testURL1
        System.out.println(redirect(testURL2)); // Should redirect to DEFAULT_URL
        System.out.println(redirect(testURL3)); // Should redirect to DEFAULT_URL
    }

    public static String redirect(String url) {
        Matcher matcher = pattern.matcher(url);
        if (matcher.matches()) {
            return url;
        }
        return DEFAULT_URL;
    }
}