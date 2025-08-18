import java.net.URL;
import java.util.function.Predicate;

public class URLRedirector {

    private final String defaultURL;

    public URLRedirector(String defaultURL) {
        this.defaultURL = defaultURL;
    }

    public String getRedirectURL(Predicate<URL> urlMatcher, URL targetURL) {
        if (urlMatcher.test(targetURL)) {
            return targetURL.toString();
        } else {
            return defaultURL;
        }
    }

    public static void main(String[] args) throws Exception {
        URLRedirector redirector = new URLRedirector("http://default.url");

        Predicate<URL> matcher = url -> "http://target.url".equals(url.toString());

        URL targetURL1 = new URL("http://target.url");
        URL targetURL2 = new URL("http://another.url");

        System.out.println(redirector.getRedirectURL(matcher, targetURL1));
        System.out.println(redirector.getRedirectURL(matcher, targetURL2));
    }
}