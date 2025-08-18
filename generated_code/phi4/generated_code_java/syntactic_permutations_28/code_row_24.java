import java.util.regex.Pattern;

public class UrlRedirector {

    private static final Pattern PATTERN = Pattern.compile("https?://(www\\.)?example\\.com/.*");

    public String getRedirectUrl(String targetUrl) {
        if (PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            // Use the original URL or some default behavior when it doesn't match
            return "https://default-redirect.com";
        }
    }

    public static void main(String[] args) {
        UrlRedirector redirector = new UrlRedirector();

        String testUrl1 = "http://www.example.com/page1";
        String testUrl2 = "https://anotherexample.com/page";

        System.out.println(redirector.getRedirectUrl(testUrl1)); // Should print: http://www.example.com/page1
        System.out.println(redirector.getRedirectUrl(testUrl2)); // Should print: https://default-redirect.com
    }
}