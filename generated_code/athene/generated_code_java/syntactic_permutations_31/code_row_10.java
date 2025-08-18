import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            return(parsedUrl.getProtocol() + "://" + parsedUrl.getHost() + parsedUrl.getPath());
        } catch (Exception e) {
            return null;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.redirect_url("https://www.example.com/path?query=param"));
    }
}