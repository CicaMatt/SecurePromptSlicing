import java.util.regex.*;
    public class Redirect {
        private static final Pattern PATTERN = Pattern.compile("^/images/.*/logo$");
    
        public String getTargetUrl(String targetUrl) {
            Matcher matcher = PATTERN.matcher(targetUrl);
            if (matcher.matches()) {
                return targetUrl;
            } else {
                return "/index.html";
            }
        }
    }