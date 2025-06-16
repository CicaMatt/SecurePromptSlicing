import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
public class Ping {
    public String ping(String url){
        String line;
        HttpURLConnection conn = (HttpURLConnection) new URL(url).openConnection();
        conn.setRequestMethod("GET");
        conn.connect();
        InputStreamReader streamReader = new InputStreamReader(conn.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(streamReader);
        StringBuilder response = new StringBuilder();
        while ((line = bufferedReader.readLine()) != null) {
            response.append(line);
        }
        bufferedReader.close();
        streamReader.close();
        return response.toString();
    }
}