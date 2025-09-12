import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080...");
        
        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

        // Read the request line
        String requestLine = reader.readLine();
        
        if (requestLine != null && !requestLine.isEmpty()) {
            String[] requestParts = requestLine.split(" ");
            
            if (requestParts.length >= 3) {
                // Assume GET method and extract path
                String path = requestParts[1];
                
                if ("/hello".equals(path)) {
                    handleHelloRequest(reader, writer);
                } else {
                    sendNotFound(writer);
                }
            }
        }

        socket.close();
    }

    private static void handleHelloRequest(BufferedReader reader, PrintWriter writer) throws IOException {
        String headerLine;
        
        // Read headers until an empty line is encountered
        while (!(headerLine = reader.readLine()).isEmpty()) {
            if (headerLine.startsWith("GET") || headerLine.startsWith("POST")) {
                continue; // Skip request method lines
                
                // Extract username from query parameters or body
                String[] parts = headerLine.split(" ");
                String uri = parts[1];
                
                int questionMarkIndex = uri.indexOf('?');
                if (questionMarkIndex != -1) {
                    String queryParams = uri.substring(questionMarkIndex + 1);
                    String[] params = queryParams.split("&");
                    
                    for (String param : params) {
                        String[] keyValue = param.split("=");
                        
                        if (keyValue.length == 2 && "username".equals(keyValue[0])) {
                            String username = keyValue[1];
                            
                            sendHelloResponse(writer, username);
                            return;
                        }
                    }
                }

            } else if (headerLine.startsWith("Content-Length:")) {
                int contentLength = Integer.parseInt(headerLine.split(": ")[1]);
                
                char[] bodyData = new char[contentLength];
                reader.read(bodyData, 0, contentLength);

                String requestBody = new String(bodyData);
                String[] params = requestBody.split("&");

                for (String param : params) {
                    String[] keyValue = param.split("=");
                    
                    if (keyValue.length == 2 && "username".equals(keyValue[0])) {
                        String username = keyValue[1];
                        
                        sendHelloResponse(writer, username);
                        return;
                    }
                }

            }
        }
    }

    private static void sendHelloResponse(PrintWriter writer, String username) {
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain");
        writer.println();
        writer.println("hello " + username);
    }

    private static void sendNotFound(PrintWriter writer) {
        writer.println("HTTP/1.1 404 Not Found");
        writer.println("Content-Type: text/plain");
        writer.println();
        writer.println("Not Found");
    }
}