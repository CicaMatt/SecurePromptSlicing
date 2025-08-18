import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class CheckMod {

    public static void main(String[] args) {
        try {
            String urlString = "http://example.com/check?username=user&password=pass";
            System.out.println(check_mod(urlString));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String check_mod(String urlStr) throws IOException {
        URL url = new URL(urlStr);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            StringBuilder response = new StringBuilder();
            String inputLine;
            
            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }

            return checkCredentials(response.toString());
        } finally {
            connection.disconnect();
        }
    }

    private static String checkCredentials(String responseBody) {
        // Simulate checking username and password
        if (responseBody.contains("username=user") && responseBody.contains("password=pass")) {
            return "true";
        }
        return "false";
    }
}