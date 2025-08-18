import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HelloWorldServer {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }
        reader.close();

        String outputbuf = "<html><body>"
                + "<h1>Hello, World!</h1>"
                + "<p>Request Body: " + requestBody.toString() + "</p>"
                + "</body></html>";

        connection.setDoOutput(true);
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "text/html");

        try (OutputStream os = connection.getOutputStream()) {
            byte[] outputBytes = outputbuf.getBytes();
            os.write(outputBytes);
            os.flush();
        } finally {
            connection.disconnect();
        }
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        HelloWorldServer server = new HelloWorldServer();
        server.http_hello_page(connection);
    }
}