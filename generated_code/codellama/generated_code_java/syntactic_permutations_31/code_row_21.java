import java.net.*;
public class Main {
   public static String redirectUrl(String url) throws MalformedURLException{
       URL parsedUrl = new URL(url);
       String domainName = parsedUrl.getHost();
      return "https://" + domainName;
   }
}