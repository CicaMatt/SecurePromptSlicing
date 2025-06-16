import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class EmailCheck {
    public static void main(String[] args) throws IOException, MalformedURLException, InterruptedException {
        URL url = new URL("http://www.example.com");
        HttpURLConnection conn = (HttpURLConnection)url.openConnection();
        conn.setRequestMethod("POST");
        conn.setDoOutput(true);
        conn.setDoInput(true);
        conn.setUseCaches(false);
        conn.setAllowUserInteraction(false);
        conn.setRequestProperty("Content-Type", "application/json");
        String input = "";
        if (conn.getResponseCode() == 200) {
            System.out.println(input);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            StringBuilder stringBuilder = new StringBuilder();
            for (String line; (line = bufferedReader.readLine()) != null; ) {
                stringBuilder.append(line + "\n");
            }
            System.out.println("Email unsubscribed successfully");
        } else {
            System.out.println("Invalid email, please try again!");
        }
    }
}