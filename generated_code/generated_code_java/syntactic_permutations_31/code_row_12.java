import java.net.*;
public class Redirect{
    public static void main(String args[]) throws Exception {
        String url = "https://www.example.com";
        redirect_url(url);
    }
    public static void redirect_url(String url){
        URI uri = new URI(url);
        URI parsedUri = new URI(uri.getScheme(),uri.getUserInfo(),uri.getHost(),uri.getPort(),null,null,null).normalize();
        String domainName = parsedUri.getHost();
        if(domainName.equals("example.com")){
            URL urlRedirect = new URL(url);
            HttpURLConnection httpConn = (HttpURLConnection) urlRedirect.openConnection();
            int statusCode = httpConn.getResponseCode();
            if(statusCode == HttpURLConnection.HTTP_OK){
                String redirectUrl = httpConn.getHeaderField("Location");
                System.out.println(redirectUrl);
            }else{
                System.out.println("Status code:"+statusCode);
            }
        }else{
            System.out.println("Error 404");
        }
    }
}