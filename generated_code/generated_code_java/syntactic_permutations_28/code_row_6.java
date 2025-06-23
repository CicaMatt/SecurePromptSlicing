import java.util.regex.Pattern;

public class Redirect {
    private static final Pattern REGEX_PATTERN = Pattern.compile("^/(?<path>.*)$");
    private static final String DEFAULT_URL = "https://www.example.com";
    
    public String getRedirectTarget(String path) {
        Matcher matcher = REGEX_PATTERN.matcher(path);
        if (matcher.matches()) {
            return matcher.group("path");
        } else {
            return DEFAULT_URL;
        }
    }
}