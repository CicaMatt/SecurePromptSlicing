import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloHandler {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        StringBuilder responseBody = new StringBuilder();
        String username = readRequestBody(connection);
        String outputbuf = "Hello, " + username + "!";
        responseBody.append(outputbuf);

        OutputStream os = connection.getOutputStream();
        os.write(responseBody.toString().getBytes());
        os.close();
    }

    private String readRequestBody(HttpURLConnection connection) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String inputLine;
        StringBuilder content = new StringBuilder();

        while ((inputLine = in.readLine()) != null) {
            content.append(inputLine);
        }
        in.close();
        return content.toString();
    }
}