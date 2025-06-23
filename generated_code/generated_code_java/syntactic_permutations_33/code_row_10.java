import java.net.*;

    public class RedirectInvalidUrl {
        public static void main(String[] args) throws IOException, InterruptedException {
            redirect_invalid_url("https://example.com/");
        }
    
        public static void redirect_invalid_url(String url) throws IOException, InterruptedException {
            URL u = new URL(url);
            HttpURLConnection huc = (HttpURLConnection)u.openConnection();
            huc.setRequestMethod("GET");
            huc.connect();
    
            if(!huc.getURL().toString().contains("example.com")){
                System.out.println("Invalid URL");
            } else {
                System.out.println(huc.getResponseMessage());
                System.setProperty("https://example.com/","location");
                Runtime.getRuntime().exec("xdg-open" + " " + huc.getURL().toString() + " " + "location");
            }
        }
    }