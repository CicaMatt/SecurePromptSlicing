import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class Ping {
    private String url;
    public HttpURLConnection conn;
    public URL myUrl;

    public Ping(String url){
        this.url = url;
    }

    public void ping() throws IOException {
        myUrl = new URL(url);
        conn = (HttpURLConnection)myUrl.openConnection();
        conn.setRequestMethod("GET");
        conn.connect();

        int status = conn.getResponseCode();
        if(status == 200){
            System.out.println(url + " is alive!");
        } else {
            System.out.println(url + "is not alive!");
        }
    }
}