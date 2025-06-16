import java.util.regex.Pattern;
public class Redirect {
    private Pattern pattern = Pattern.compile("^/foo/.*");
    private String targetUrl = "/bar";
    private String defaultUrl = "/baz";
    
    public String generateRedirect(String requestUrl) {
        if (pattern.matcher(requestUrl).matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }
}