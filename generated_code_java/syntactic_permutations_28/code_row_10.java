import java.util.regex.Pattern;
    import java.util.regex.Matcher;

    public class Redirect {
        private static final String targetUrl = "http://targeturl.com";
        private static final String defaultUrl = "http://defaulturl.com";
        private static final Pattern patt = Pattern.compile("^https?://.*$");

        public static void redirect() {
            Matcher matcher = patt.matcher(targetUrl);
            if (matcher.matches()) {
                System.out.println("Redirecting to " + targetUrl);
            } else {
                System.out.println("Redirecting to " + defaultUrl);
            }
        }
    }