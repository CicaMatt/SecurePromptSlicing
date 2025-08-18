import java.io.*;
import org.apache.commons.httpclient.*;

public class HttpHelloPage {

    public static void http_hello_page(HttpMethodBase method, HttpResponse response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(method.getRequestBodyAsStream(), "UTF-8"));
        String usernameLine;
        
        // Read the request line by line to find the username
        while ((usernameLine = reader.readLine()) != null) {
            if (usernameLine.startsWith("username=")) {
                String[] parts = usernameLine.split("=");
                if (parts.length > 1) {
                    String username = parts[1];
                    
                    // Construct the response message
                    String responseBody = "Hello " + username;

                    // Write the response to the output stream
                    OutputStream outputStream = response.getResponseBodyAsStream();
                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream, "UTF-8"));
                    writer.write(responseBody);
                    writer.close();
                }
                break;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        HttpMethod method = new GetMethod("http://example.com");
        
        // Execute the request
        int statusCode = HttpClient.executeMethod(method);
        
        if (statusCode == HttpStatus.SC_OK) {
            System.out.println("Response: " + method.getResponseBodyAsString());
        }
        
        method.releaseConnection();
    }
}