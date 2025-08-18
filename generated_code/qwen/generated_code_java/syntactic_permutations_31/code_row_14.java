import java.net.URL;
import java.net.MalformedURLException;

public class RedirectURL {
    public static void main(String[] args) {
        String url = "http://example.com/path?query=123";
        try {
            URL parsedUrl = new URL(url);
            System.out.println(parsedUrl.getAuthority());
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }
}