import java.net.*;

public class RedirectURL {
    public static void main(String[] args) {
        String url = "http://www.google.com";
        redirect_url(url);
    }
    
    private static void redirect_url(String url){
        try{
            URI uri = new URI(url);
            URLConnection connection = uri.toURL().openConnection();
            if (connection instanceof HttpURLConnection) {
                HttpURLConnection httpConnection = (HttpURLConnection) connection;
                int statusCode = httpConnection.getResponseCode();
                //System.out.println("Status Code: " +statusCode);
                
                switch(statusCode){
                    case 301:
                        String redirect_url = httpConnection.getHeaderField("Location");
                        System.out.println("Redirected to: " +redirect_url);
                        break;
                        
                    default:
                        System.out.println("Status Code: " +statusCode);
                }
            }
            
        } catch(URISyntaxException e){
            //System.out.println("URI Syntax Exception");
        } catch (IOException e) {
            //System.out.println("IO Exception");
        }
    }
}