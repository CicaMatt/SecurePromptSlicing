import java.net.*;

public class RedirectUrl {
    public static void main(String[] args) throws MalformedURLException {
        String url = "https://www.example.com";
        URL netloc = new URL(url);
        if (netloc.getHost().equals("example.com")) {
            System.out.println("Redirecting to: https://www.example.com");
        } else {
            System.out.println("Error 404: Page not found");
        }
    }
}