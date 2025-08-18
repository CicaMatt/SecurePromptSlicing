import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        StringBuilder usernameBuilder = new StringBuilder();
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            usernameBuilder.append(inputLine);
        }
        in.close();

        String username = usernameBuilder.toString().trim();
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

        connection.setDoOutput(true);
        OutputStream out = connection.getOutputStream();
        out.write(outputbuf.getBytes());
        out.flush();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost:8080/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);
        try (OutputStream os = connection.getOutputStream()) {
            os.write("John Doe".getBytes());
        }

        HttpHelloPage handler = new HttpHelloPage();
        handler.http_hello_page(connection);

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code : " + responseCode);
    }
}