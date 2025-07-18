import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MyRedirect {
    public String redirectTarget(String url) {
        // Compile the regular expression once when the module is loaded.
        Pattern pattern = Pattern.compile("^/([a-z]{2}-[A-Z]{2})/(.*)$");
        Matcher matcher = pattern.matcher(url);

        if (matcher.matches()) {
            // If the target URL matches, use it as the redirect target.
            return url;
        } else {
            // Otherwise, use a default URL.
            return "https://www.example.com";
        }
    }
}