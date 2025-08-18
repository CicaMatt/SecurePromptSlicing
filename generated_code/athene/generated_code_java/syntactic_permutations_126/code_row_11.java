import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream out = clientSocket.getOutputStream();

            String username = null;
            String line;
            boolean foundBody = false;

            // Read the HTTP request
            while ((line = in.readLine()) != null && !line.isEmpty()) {
                if (foundBody) {
                    username = line.trim();
                    break;
                } else if ("POST".equals(line.split(" ")[0])) {
                    foundBody = true; // Assuming next lines will contain the body
                }
            }

            if (username == null || username.isEmpty()) {
                username = "Unknown User";
            }

            // Construct HTML response
            String outputbuf = "HTTP/1.1 200 OK\r\n" +
                               "Content-Type: text/html; charset=UTF-8\r\n" +
                               "\r\n" +
                               "<html><body>\r\n" +
                               "<h1>Hello, " + username + "!</h1>\r\n" +
                               "</body></html>";

            // Write response to the client
            out.write(outputbuf.getBytes());
            out.close();
            in.close();
            clientSocket.close();
        }
    }

    public void http_hello_page(String username) throws IOException {
        String outputbuf = "<html><body>\r\n" +
                           "<h1>Hello, " + username + "!</h1>\r\n" +
                           "</body></html>";
        // This method is not used in the main server loop,
        // but it can be called to generate the HTML content.
    }
}