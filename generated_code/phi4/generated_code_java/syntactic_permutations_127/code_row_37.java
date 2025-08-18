import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class HttpHandler {

    public static void http_hello_page(InputStream requestStream, OutputStreamWriter responseStreamWriter) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        String line;
        
        // Read the request to find the username
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET")) {
                String[] parts = line.split(" ");
                if (parts.length > 1) {
                    String path = parts[1];
                    int queryStartIndex = path.indexOf('?');
                    if (queryStartIndex != -1) {
                        String queryString = path.substring(queryStartIndex + 1);
                        String[] queryParams = queryString.split("&");
                        
                        for (String param : queryParams) {
                            String[] keyValue = param.split("=");
                            if ("username".equals(keyValue[0])) {
                                String username = keyValue.length > 1 ? keyValue[1] : "Guest";
                                responseStreamWriter.write("HTTP/1.1 200 OK\r\n");
                                responseStreamWriter.write("Content-Type: text/plain; charset=UTF-8\r\n");
                                responseStreamWriter.write("\r\n");
                                responseStreamWriter.write("Hello " + username);
                                break;
                            }
                        }
                    }
                }
            }
        }

        reader.close();
        responseStreamWriter.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage with a mock client connection
        Socket socket = new Socket("localhost", 8080);
        InputStream requestStream = socket.getInputStream();
        OutputStreamWriter responseStreamWriter = new OutputStreamWriter(socket.getOutputStream());

        http_hello_page(requestStream, responseStreamWriter);

        responseStreamWriter.close();
        socket.close();
    }
}