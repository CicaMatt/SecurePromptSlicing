import java.util.regex.Pattern;

public class UrlRedirector {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");

    public String getRedirectUrl(String url) {
        if (TARGET_URL_PATTERN.matcher(url).matches()) {
            return url;
        }
        return null; // or any default behavior you want
    }

    public static void main(String[] args) {
        UrlRedirector redirector = new UrlRedirector();
        String testUrl = "your-test-url-here";
        
        String redirectUrl = redirector.getRedirectUrl(testUrl);
        if (redirectUrl != null) {
            System.out.println("Redirect to: " + redirectUrl);
        } else {
            System.out.println("No redirect.");
        }
    }
}


Replace `"your-regex-here"` with the actual regular expression you want to compile and use. Replace `"your-test-url-here"` with a sample URL for testing.