import java.net.*;
public class Main{
    public static void main(String[] args) {
        String url = "http://example.com";
        URL parsed_url;
        try {
            parsed_url=new URL(url);
            if (parsed_url.getHost().endsWith(".example.com")){
                System.out.println("redirecting...");
            } else {
                System.out.println("not redirecting...");
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }
}