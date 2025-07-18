import java.util.*;
import com.google.common.base.Strings;
public class Redirect {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("http://([a-z]+).example.com");
    public String getTargetUrl(String url) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return "http://redirect.example.com";
        }
    }
}