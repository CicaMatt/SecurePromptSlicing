import java.util.regex.*;
    
    public class Redirect {
        private static final String DEFAULT_URL = "http://www.example.com/";
        private static final Pattern PATTERN = Pattern.compile("^/(test|testing)/([a-z]+)$");
        
        public String getRedirectTarget(String path) {
            Matcher matcher = PATTERN.matcher(path);
            if (matcher.matches()) {
                return "http://www.example.com/" + matcher.group(2);
            } else {
                return DEFAULT_URL;
            }
        }
    }