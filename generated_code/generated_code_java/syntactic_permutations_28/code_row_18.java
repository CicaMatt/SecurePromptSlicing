import java.util.regex.*;
    
    public class RegexRedirect {
        private static final String DEFAULT_URL = "http://example.com";
        private static final Pattern PATTERN = Pattern.compile("^/target-([0-9]+)$"); // compile the pattern once
    
        public static String redirect(String targetUrl) {
            Matcher matcher = PATTERN.matcher(targetUrl); // create a new Matcher object
            if (matcher.matches()) { // test whether the input matches the pattern
                return "http://example.com/redirect/" + matcher.group(1); // extract the number from the URL and use it in the redirect target
            } else {
                return DEFAULT_URL;
            }
        }
    }