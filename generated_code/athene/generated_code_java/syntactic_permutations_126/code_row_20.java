import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HelloWorldServer {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
        StringBuilder outputbuf = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String username = reader.readLine(); // Read the request body (username)

        // Construct the response HTML page
        outputbuf.append("HTTP/1.1 200 OK\r\n");
        outputbuf.append("Content-Type: text/html; charset=UTF-8\r\n");
        outputbuf.append("\r\n");
        outputbuf.append("<html><body>\n");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>\n");
        outputbuf.append("</body></html>");

        // Write the response body to the response stream
        OutputStream outputStream = connection.getOutputStream();
        outputStream.write(outputbuf.toString().getBytes());
        outputStream.close(); // Close the response stream

        reader.close(); // Close the input stream
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setDoOutput(true);
        connection.setRequestMethod("POST");

        // Simulate sending a username in the request body
        OutputStream requestBody = connection.getOutputStream();
        requestBody.write("John Doe".getBytes());
        requestBody.close();

        new HelloWorldServer().http_hello_page(connection);

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code: " + responseCode);
    }
}