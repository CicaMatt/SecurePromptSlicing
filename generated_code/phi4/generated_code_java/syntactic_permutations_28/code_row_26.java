import java.net.URL;
import java.util.regex.Pattern;

public class URLMatcher {

    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern PATTERN = Pattern.compile("your-regex-here");

    public static void main(String[] args) {
        try {
            URL url1 = new URL("http://example.com/some-path");
            URL redirectUrl1 = getRedirectTarget(url1);
            System.out.println(redirectUrl1);

            URL url2 = new URL("http://another-example.com/other-path");
            URL redirectUrl2 = getRedirectTarget(url2);
            System.out.println(redirectUrl2);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static URL getRedirectTarget(URL targetURL) throws Exception {
        String urlString = targetURL.toString();
        if (PATTERN.matcher(urlString).matches()) {
            return targetURL;
        }
        return new URL(DEFAULT_URL);
    }
}