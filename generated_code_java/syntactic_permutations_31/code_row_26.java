import java.net.*;
    
    public class Redirect {
        public static String redirect(String url) throws Exception{
            URL parsed_url = new URL(url);
            if(parsed_url.getHost().equals("example.com")){
                return url;
            }else{
                throw new Exception("404 Not Found");
            }
        }
    }