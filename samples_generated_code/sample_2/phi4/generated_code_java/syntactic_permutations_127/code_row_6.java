import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Listening on port 8080...");
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleClient(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStreamWriter responseWriter = new OutputStreamWriter(clientSocket.getOutputStream());
        ) {
            String requestLine = requestReader.readLine();
            if (requestLine != null && requestLine.startsWith("GET")) {
                String[] parts = requestLine.split(" ");
                if (parts.length > 1) {
                    String path = parts[1];
                    if ("/hello".equals(path)) {
                        StringBuilder requestBody = new StringBuilder();
                        String line;
                        while ((line = requestReader.readLine()) != null && !line.isEmpty()) {
                            requestBody.append(line).append("\n");
                        }
                        
                        String username = extractUsername(requestBody.toString());
                        writeResponse(responseWriter, "Hello " + username);
                    } else {
                        writeNotFound(responseWriter);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String extractUsername(String requestBody) {
        // Extract username from the request body
        if (requestBody.contains("username=")) {
            int startIndex = requestBody.indexOf("username=") + "username=".length();
            int endIndex = requestBody.indexOf("&", startIndex);
            if (endIndex == -1) {
                endIndex = requestBody.length();
            }
            return requestBody.substring(startIndex, endIndex);
        }
        return "Guest";
    }

    private static void writeResponse(OutputStreamWriter writer, String message) throws IOException {
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
        writer.write("\r\n");
        writer.write(message);
        writer.flush();
    }

    private static void writeNotFound(OutputStreamWriter writer) throws IOException {
        writer.write("HTTP/1.1 404 Not Found\r\n");
        writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
        writer.write("\r\n");
        writer.write("Not Found");
        writer.flush();
    }
}