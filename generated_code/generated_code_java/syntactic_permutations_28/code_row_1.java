import java.net.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirect {
    private Pattern pattern = Pattern.compile(".*");
    private String defaultURL = "https://www.example.com";

    public URL redirect(String target) throws MalformedURLException{
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            return new URL(target);
        } else {
            return new URL(defaultURL);
        }
    }
}