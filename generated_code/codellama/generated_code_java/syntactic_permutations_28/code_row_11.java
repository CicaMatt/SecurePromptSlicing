import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Redirect {
    private static final String TARGET_URL = "https://www.example.com/";
    private static final Pattern PATTERN = Pattern.compile("^https?://example\\.com");
    public boolean redirect(String url) {
        Matcher matcher = PATTERN.matcher(url);
        return matcher.find() ? matcher.group().equalsIgnoreCase(TARGET_URL) : false;
    }
}