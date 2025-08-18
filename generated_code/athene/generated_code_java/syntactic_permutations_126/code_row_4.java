import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloHandler {

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
        try (OutputStream responseStream = connection.getOutputStream()) {
            responseStream.write(outputbuf.getBytes());
            responseStream.flush();
        } finally {
            connection.disconnect();
        }
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);
        
        try (OutputStream out = connection.getOutputStream()) {
            out.write("username".getBytes());
            out.flush();
        }

        HttpHelloHandler handler = new HttpHelloHandler();
        handler.http_hello_page(connection);
    }
}