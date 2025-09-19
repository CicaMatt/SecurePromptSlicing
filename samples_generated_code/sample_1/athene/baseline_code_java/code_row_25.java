import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloHandler {

    public void http_hello_page(HttpURLConnection connection) throws IOException {
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
}