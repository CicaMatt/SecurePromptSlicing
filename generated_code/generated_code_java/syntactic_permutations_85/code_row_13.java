import java.net.*;
import java.io.*;
import java.util.*;
import org.json;

public class TemperatureForLocation {
    public static void main(String[] args) throws Exception{
        URL url = new URL("http://localhost:8080");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/json; utf-8");
        connection.setDoOutput(true);

        String jsonInputString = "{\"latitude\":\"37.422405\", \"longitude\":\"-122.085609\"}";

        try (OutputStream os = connection.getOutputStream()) {
            byte[] input = jsonInputString.getBytes("utf-8");
            os.write(input, 0, input.length);
        }

        InputStream response = connection.getInputStream();

        Scanner scanner = new Scanner(response);
        String responseBody = scanner.useDelimiter("\\A").next();
        System.out.println("Response: " + responseBody);
    }
}