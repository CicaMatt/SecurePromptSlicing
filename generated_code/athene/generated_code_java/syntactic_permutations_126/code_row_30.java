import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpServerHandler {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        StringBuilder username = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                username.append(line);
            }
        }

        String outputbuf = "<html><body><h1>Hello, " + username.toString() + "!</h1></body></html>";

        connection.setDoOutput(true);
        connection.getResponseCode(); // Trigger response
        try (OutputStream out = connection.getOutputStream()) {
            out.write(outputbuf.getBytes());
            out.flush();
        }
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost:8080/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

        // Simulate sending a username in the request body
        try (OutputStream os = connection.getOutputStream()) {
            String requestBody = "username=JohnDoe";
            os.write(requestBody.getBytes());
        }

        HttpServerHandler handler = new HttpServerHandler();
        handler.http_hello_page(connection);
    }
}