import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        int port = 8080; // You can choose any available port

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port " + port);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleClientRequest(clientSocket);
            }
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        try (
            BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream responseOutputStream = clientSocket.getOutputStream()
        ) {

            // Read the request line
            String requestLine = requestReader.readLine();
            System.out.println("Request: " + requestLine);

            // Assume a simple GET request with query string like ?username=JohnDoe
            String[] headers = new String[16];
            int index = 0;
            String line;
            while (!(line = requestReader.readLine()).isEmpty()) {
                if (index < headers.length) {
                    headers[index++] = line;
                }
            }

            // Parse the query string for username
            String username = null;
            for (String header : headers) {
                if (header.startsWith("GET")) {
                    int questionMarkIndex = header.indexOf('?');
                    if (questionMarkIndex != -1) {
                        String queryString = header.substring(questionMarkIndex + 1);
                        String[] pairs = queryString.split("&");
                        for (String pair : pairs) {
                            String[] keyValue = pair.split("=");
                            if ("username".equals(keyValue[0])) {
                                username = keyValue.length > 1 ? keyValue[1] : null;
                                break;
                            }
                        }
                    }
                }
            }

            // Construct the response
            String responseMessage = "hello ";
            responseMessage += (username != null) ? username : "guest";
            responseMessage += "\r\n";

            byte[] responseBytes = responseMessage.getBytes("UTF-8");

            // Write HTTP headers and body to the response
            responseOutputStream.write(("HTTP/1.1 200 OK\r\n" +
                    "Content-Type: text/plain; charset=UTF-8\r\n" +
                    "Content-Length: " + responseBytes.length + "\r\n" +
                    "Connection: close\r\n" +
                    "\r\n").getBytes("UTF-8"));
            responseOutputStream.write(responseBytes);

            responseOutputStream.flush();
        } finally {
            clientSocket.close();
        }
    }
}


This code sets up a basic HTTP server that listens on port 8080. It reads the request from the client, parses it for the username from the query string, constructs a "hello [username]" message, and sends this response back to the client. The server handles one connection at a time in a blocking manner for simplicity.