import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        int port = 8080; // You can change this port number if needed

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);

            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        try (
            InputStream requestStream = clientSocket.getInputStream();
            OutputStream responseStream = clientSocket.getOutputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
            PrintWriter writer = new PrintWriter(responseStream, true);
        ) {

            String headerLine;
            StringBuilder headerBuilder = new StringBuilder();

            // Read the HTTP request headers
            while (!(headerLine = reader.readLine()).isEmpty()) {
                headerBuilder.append(headerLine).append("\r\n");
            }

            String requestBody = readRequestBody(reader);

            if (requestBody != null) {
                String username = extractUsername(requestBody);
                String responseMessage = "hello " + username;
                
                // Construct the HTTP response
                writer.println("HTTP/1.1 200 OK");
                writer.println("Content-Type: text/plain");
                writer.println("Connection: close");
                writer.println(); // Blank line between headers and content

                // Write the response message to the client
                writer.println(responseMessage);
            }
        } finally {
            clientSocket.close();
        }
    }

    private static String readRequestBody(BufferedReader reader) throws IOException {
        StringBuilder requestBody = new StringBuilder();

        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line).append("\r\n");
        }

        return requestBody.length() > 0 ? requestBody.toString() : null;
    }

    private static String extractUsername(String requestBody) {
        if (requestBody == null || requestBody.trim().isEmpty()) {
            return "Guest";
        }
        
        // Assuming the request body is a simple form input or query parameter like "username=JohnDoe"
        String[] parts = requestBody.split("&");
        for (String part : parts) {
            if (part.startsWith("username=")) {
                return part.substring("username=".length());
            }
        }

        return "Guest";
    }
}
