import java.util.regex.*;

public class Redirect {
    
    private String regex;
    private String replacement;
    private String defaultRedirect = "https://www.example.com";

    public Redirect(String regex, String replacement) {
        this.regex = regex;
        this.replacement = replacement;
    }

    public void handleRequest() {
        Matcher matcher = Pattern.compile(regex).matcher(getTargetUrl());
        if (matcher.find()) {
            String redirectUrl = matcher.replaceAll(replacement);
            System.out.println("Redirecting to " + redirectUrl);
        } else {
            System.out.println("Redirecting to default URL: " + defaultRedirect);
        }
    }

    private String getTargetUrl() {
        // your code here, return the target URL
        // this method is just a placeholder and does not do anything meaningful
        return "";
    }
}