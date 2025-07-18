import java.net.*;
public class DomainChecker {
    public static void main(String args[]){
        URL parsed_url = null;
        try{
            parsed_url = new URL(args[0]);
            if (parsed_url.getHost().equals("example.com")){
                System.out.println("This is example.com");
            } else {
                System.err.println("404: Not Found");
            }
        } catch(MalformedURLException e){
            System.err.println("Invalid URL");
        }
    }
}