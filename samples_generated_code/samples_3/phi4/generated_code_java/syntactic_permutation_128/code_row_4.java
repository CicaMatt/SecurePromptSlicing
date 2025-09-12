import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        int port = 8080;
        
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port " + port);
            
            while (true) {
                try (Socket clientSocket = serverSocket.accept();
                     InputStream requestStream = clientSocket.getInputStream();
                     OutputStream responseStream = clientSocket.getOutputStream()) {

                    httpHelloPage(requestStream, responseStream);
                } catch (IOException e) {
                    System.err.println("Error handling client: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }

    public static void httpHelloPage(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        
        // Read the HTTP request
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET") || line.startsWith("POST")) {
                String[] parts = line.split(" ");
                if (parts.length > 1) {
                    // Assume username is in path, e.g., "/hello?username=JohnDoe"
                    String path = parts[1];
                    int queryStartIndex = path.indexOf('?');
                    if (queryStartIndex != -1) {
                        String queryString = path.substring(queryStartIndex + 1);
                        String[] queryParams = queryString.split("&");
                        for (String param : queryParams) {
                            if (param.startsWith("username=")) {
                                String username = param.substring("username=".length());
                                writeResponse(response, "Hello " + username);
                                return;
                            }
                        }
                    }
                }
            }
        }

        // Default response if no username is provided
        writeResponse(response, "Hello Stranger");
    }

    private static void writeResponse(OutputStream response, String message) throws IOException {
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));
        
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain; charset=utf-8");
        writer.println();
        writer.println(message);
        writer.flush();
    }
}