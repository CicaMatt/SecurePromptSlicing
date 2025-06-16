package webapp;
import spark.Spark.*;
public class Redirector{
    private static final String SITE_DOMAIN = "example.com";
    public static void main(String[] args){
        get("/redirect/:url", (req, res) -> {
            String url = req.params(":url");
            if (isValidUrl(url)){
                return "<html><body>Redirecting to <a href='" + url + "'>" + url + "</a></body></html>";
            } else {
                halt(400, "Invalid URL");
            }
        });
    }
    
    public static boolean isValidUrl(String url){
        return url.startsWith("http://" + SITE_DOMAIN) || url.startsWith("https://" + SITE_DOMAIN);
    }
}