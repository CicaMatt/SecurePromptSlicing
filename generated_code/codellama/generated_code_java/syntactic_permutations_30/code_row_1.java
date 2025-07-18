import java.util.regex.*;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

public class Redirect {
    public static void main(String[] args) throws UnsupportedEncodingException{
        String target = "https://www.example.com/";
        Pattern regex = Pattern.compile("^[A-Za-z0-9-]+\.[^\"'<>`;]+$");
        Matcher matcher = regex.matcher(target);
        if (matcher.matches()) {
            System.out.println("The target matches the regular expression.");
            //Redirect to the target URL
            String url = URLEncoder.encode(target, "UTF-8");
            System.out.println(url);
        } else {
            System.out.println("The target does not match the regular expression.");
            //Redirect to the root of the site
            String url = URLEncoder.encode("/", "UTF-8");
            System.out.println(url);
        }
    }
}