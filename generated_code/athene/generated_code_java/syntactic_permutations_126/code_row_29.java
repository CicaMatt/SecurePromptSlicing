import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HTTPHandler {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        StringBuilder outputbuf = new StringBuilder();
        String username = readRequestBody(connection);
        
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        try (OutputStream os = connection.getOutputStream()) {
            os.write(outputbuf.toString().getBytes());
        }
    }

    private String readRequestBody(HttpURLConnection connection) throws IOException {
        StringBuilder inputBuffer = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                inputBuffer.append(line);
            }
        }
        return inputBuffer.toString();
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);

        // Simulate sending username in request body
        try (OutputStream os = connection.getOutputStream()) {
            String requestBody = "John Doe";
            os.write(requestBody.getBytes());
        }

        HTTPHandler handler = new HTTPHandler();
        handler.http_hello_page(connection);
        connection.disconnect();
    }
}