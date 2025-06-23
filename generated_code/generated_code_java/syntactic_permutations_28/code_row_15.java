import java.util.regex.*;

    public class Redirect {
        private static final String DEFAULT_URL = "https://www.google.com/";
        private static final Pattern regex = 
            Pattern.compile("^[a-zA-Z0-9]+$");
    
        public static void main(String[] args) {
            String redirectUrl = getRedirectUrl(args[0]);
            System.out.println(redirectUrl);
        }
    
        private static String getRedirectUrl(String url) {
            Matcher matcher = regex.matcher(url);
            if (matcher.matches()) {
                return url;
            } else {
                return DEFAULT_URL;
            }
        }
    }