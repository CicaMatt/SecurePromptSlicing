import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.net.URL;
public class Redirect {
    private static final String DEFAULT_REDIRECT = "https://www.example.com/";
    private Pattern pattern = Pattern.compile("^/[a-zA-Z0-9]{4,16}$");
    public void redirect(String target) throws Exception {
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            URL url = new URL(target);
            System.out.println("redirecting to " + url.toString());
            return;
        }
        System.out.println("redirecting to default page");
        URL url = new URL(DEFAULT_REDIRECT);
    }
}