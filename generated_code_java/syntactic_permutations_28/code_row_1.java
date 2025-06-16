import java.util.regex.Matcher;
import java.util.regex.Pattern;
 
public class Redirect {
    private static Pattern pattern = Pattern.compile("http://www.example.com/");
 
    public void execute(String targetUrl) {
        String redirectTarget = getRedirectTarget(targetUrl);
        // Do the redirect...
    }
 
    private String getRedirectTarget(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return "http://www.example.com/default";
        }
    }
}