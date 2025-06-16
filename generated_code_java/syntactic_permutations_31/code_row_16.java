import java.net.*;
class Redirect_url{
    public static void main(String[] args){
        String url="http://example.com";
        if(!get_network_location(url).equals("example.com")){
            System.out.println("Error 404 : Not found");
        }
    }
    
    public static String get_network_location(String url){
        URL parsed_url=new URL(url);
        String network_location=parsed_url.getHost();
        return network_location;
    }
}