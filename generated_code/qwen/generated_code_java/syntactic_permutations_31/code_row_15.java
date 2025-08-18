import java.net.URL;
import java.net.MalformedURLException;

public class RedirectUrlExample {

    public static void main(String[] args) {
        String url = "https://www.example.com/path?query=123";
        try {
            System.out.println(redirect_url(url));
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }

    public static String redirect_url(String url) throws MalformedURLException {
        URL parsedUrl = new URL(url);
        return parsedUrl.getAuthority();
    }
}