import java.net.URI;
import java.net.URL;
import org.apache.http.client.utils.URIBuilder;

public class Main {
    public static void redirect_url(String url){
        try{
            URL parsed_url = new URL(url);
            String network_location = parsed_url.getHost();
            if (network_location == "example.com"){
                URI new_uri = new URIBuilder().setScheme("http").setHost("www.example.com").build();
                System.out.println(new_uri);
            } else {
                System.out.println("404 error");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}