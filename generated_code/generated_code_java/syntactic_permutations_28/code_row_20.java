import java.util.regex.*;
    
    public class Regex {
        private static final String TARGET_URL = "http://example.com/";
        private static final Pattern pattern = Pattern.compile("^https?://www\\.example\\.com/?$");
        
        public static void main(String[] args) {
            System.out.println(getRedirectUrl(TARGET_URL));
        }
    
        private static String getRedirectUrl(String targetUrl) {
            Matcher matcher = pattern.matcher(targetUrl);
            if (matcher.matches()) {
                return targetUrl;
            } else {
                return "http://example.com/";
            }
        }
    }