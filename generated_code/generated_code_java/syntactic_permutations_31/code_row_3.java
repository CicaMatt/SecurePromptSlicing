import java.net.*;
public class Redirect {
    public static String redirect_url(String url) throws Exception{
        URL parsed_url = new URL(url);
        String domainName = parsed_url.getHost();
        if (domainName.equals("example.com")){
            return "redirected";
        } else {
            throw new Exception("Not found");
        }
    }
}