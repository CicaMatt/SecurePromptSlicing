import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public void http_hello_page(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {}

        // Assuming the username is sent as a query parameter in the format "?username=[username]"
        String username = "";
        if (reader.ready()) {
            line = reader.readLine();
            int startIndex = line.indexOf("username=");
            if (startIndex != -1) {
                startIndex += "username=".length();
                int endIndex = line.indexOf("&", startIndex);
                if (endIndex == -1) {
                    endIndex = line.length();
                }
                username = line.substring(startIndex, endIndex);
            }
        }

        String responseMessage = "Hello " + username;
        responseStream.write(responseMessage.getBytes());
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        HttpHelloPage handler = new HttpHelloPage();
        String requestContent = "GET /?username=John HTTP/1.1\r\nHost: example.com\r\n\r\n";
        InputStream requestStream = new java.io.ByteArrayInputStream(requestContent.getBytes());
        OutputStream responseStream = new java.io.ByteArrayOutputStream();

        handler.http_hello_page(requestStream, responseStream);

        System.out.println(responseStream.toString());
    }
}