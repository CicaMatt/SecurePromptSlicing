import java.io.*;
import java.net.*;

public class UnsubscribeUser {
    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/unsubscribUser?email=user@mail.com");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String inputLine;
        while ((inputLine = reader.readLine()) != null) {
            System.out.println(inputLine);
        }
        reader.close();
    }
}