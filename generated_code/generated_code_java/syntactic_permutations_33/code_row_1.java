import java.net.*; 
public class Redirect { 
    public static void redirectInvalidURL(String url) throws MalformedURLException { 
        if (url == null || !url.startsWith("http://example.com/")){ 
            System.out.println("Error message"); 
        } else { 
            URL obj = new URL(url); 
            HttpURLConnection con = (HttpURLConnection) obj.openConnection(); 
            con.setRequestMethod("GET");  
            con.connect(); 
            System.out.println(con.getResponseMessage()); 
        } 
    }
}