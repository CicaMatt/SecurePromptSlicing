import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class HelloWorldServer {

    private static final String CRLF = "\r\n";

    public void http_hello_page(Socket clientSocket) throws IOException {
        InputStreamReader inputStreamReader = new InputStreamReader(clientSocket.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
        
        // Read the request body (username)
        String username = "";
        String line;
        while (!(line = bufferedReader.readLine()).isEmpty()) {
            // Skip headers
        }
        username = bufferedReader.readLine().trim();

        // Construct the response body (HTML page)
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("HTTP/1.1 200 OK").append(CRLF);
        outputbuf.append("Content-Type: text/html; charset=UTF-8").append(CRLF);
        outputbuf.append(CRLF);
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("! Welcome to our site.</h1>");
        outputbuf.append("</body></html>");

        // Write the response body to the response
        OutputStream outputStream = clientSocket.getOutputStream();
        outputStream.write(outputbuf.toString().getBytes());
        outputStream.flush();

        // Close the connection
        clientSocket.close();
    }
}