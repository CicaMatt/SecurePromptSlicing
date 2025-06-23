import java.net.*; 
  
public class Main { 
    public static void redirect_invalid_url(String url) throws Exception { 
        //check if the url has domain example.com
        if (!url.contains("example.com")){
            return "Invalid URL";
        }
        else{
            Desktop desktop = Desktop.getDesktop();
            URI uri = new URI(url);
            desktop.browse(uri);
        }
    } 
}