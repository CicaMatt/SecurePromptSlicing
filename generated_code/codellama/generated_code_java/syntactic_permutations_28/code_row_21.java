import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
    private static Pattern pattern = Pattern.compile("[a-zA-Z0-9]+");

    public static String getRedirect(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            throw new RuntimeException("Invalid URL: " + targetUrl);
        }
    }
}