import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class HttpServer {

    public static void http_hello_page(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(responseStream));

        // Read the request line
        String requestLine = reader.readLine();
        
        if (requestLine != null && requestLine.startsWith("GET")) {
            String[] tokens = requestLine.split(" ");
            
            if (tokens.length >= 2) {
                String path = tokens[1];
                
                if ("/hello".equals(path)) {
                    // Read headers and find "username" parameter
                    boolean usernameFound = false;
                    String line;
                    while ((line = reader.readLine()) != null && !line.isEmpty()) {
                        if (line.startsWith("GET") || line.startsWith("POST")) continue; // Ignore HTTP methods
                        if (line.toLowerCase().startsWith("cookie:")) {
                            line = line.substring(line.indexOf('=') + 1).trim();
                            if (line.startsWith("\"") && line.endsWith("\"")) {
                                String username = line.substring(1, line.length() - 1);
                                writer.write("HTTP/1.1 200 OK\r\n");
                                writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                                writer.write("\r\n");
                                writer.write("Hello " + username + "\r\n");
                                usernameFound = true;
                            }
                        }
                    }

                    if (!usernameFound) {
                        // If username is not found in the cookie, return a 400 Bad Request
                        writer.write("HTTP/1.1 400 Bad Request\r\n");
                        writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                        writer.write("\r\n");
                        writer.write("No username provided.\r\n");
                    }
                } else {
                    // If path is not /hello, return a 404 Not Found
                    writer.write("HTTP/1.1 404 Not Found\r\n");
                    writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                    writer.write("\r\n");
                    writer.write("Page not found.\r\n");
                }
            } else {
                // If request line is malformed, return a 400 Bad Request
                writer.write("HTTP/1.1 400 Bad Request\r\n");
                writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                writer.write("\r\n");
                writer.write("Malformed request.\r\n");
            }
        } else {
            // If the request is not a GET, return a 405 Method Not Allowed
            writer.write("HTTP/1.1 405 Method Not Allowed\r\n");
            writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
            writer.write("\r\n");
            writer.write("Only GET method is supported.\r\n");
        }

        writer.flush();
    }
}