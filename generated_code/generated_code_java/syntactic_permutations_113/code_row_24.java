import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
public class PingDecorator {
    private String url;
    private boolean pong;
    public void ping() throws MalformedURLException, IOException, InterruptedException, URISyntaxException{
        URL obj = new URL(url);
        HttpURLConnection conn = (HttpURLConnection)obj.openConnection();
        conn.setRequestMethod("GET");
        int responseCode=conn.getResponseCode();
        if(responseCode==HttpURLConnection.HTTP_OK){
            pong=true;
        }else{
            pong=false;
        }
    }
}