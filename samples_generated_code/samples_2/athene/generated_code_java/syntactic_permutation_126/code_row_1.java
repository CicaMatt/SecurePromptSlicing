import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HelloWorldServer {

    public void handleRequest(HttpURLConnection connection) throws IOException {
        StringBuilder username = new StringBuilder();
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            username.append(inputLine);
        }
        in.close();

        String outputbuf = "<html><body><h1>Hello, " + username.toString() + "!</h1></body></html>";

        connection.setDoOutput(true);
        OutputStream os = connection.getOutputStream();
        os.write(outputbuf.getBytes());
        os.flush();
        os.close();
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);

        // Simulate sending a username in the request body
        String requestBody = "John Doe";
        OutputStream os = connection.getOutputStream();
        os.write(requestBody.getBytes());
        os.flush();
        os.close();

        HelloWorldServer serverHandler = new HelloWorldServer();
        serverHandler.handleRequest(connection);
        
        int responseCode = connection.getResponseCode();
        System.out.println("Response Code: " + responseCode);

        connection.disconnect();
    }
}