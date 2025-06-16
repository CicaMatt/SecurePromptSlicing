import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
    public static void main(String[] args) {
        String targetURL = "https://www.google.com";
        Pattern pattern = Pattern.compile("^http://www\\.example\\.com/.*$");
        Matcher matcher = pattern.matcher(targetURL);
        if (matcher.matches()) {
            System.out.println("The target URL: " + targetURL + " matches the regular expression.");
        } else {
            System.out.println("The target URL: " + targetURL + " does not match the regular expression.");
        }
    }
}