import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        InputStream inputStream = clientSocket.getInputStream();
        OutputStream outputStream = clientSocket.getOutputStream();

        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));

        String requestLine;
        StringBuilder requestBody = new StringBuilder();
        
        while (!(requestLine = reader.readLine()).isEmpty()) {
            if (requestLine.startsWith("POST")) {
                int contentLength = 0;
                while (!(requestLine = reader.readLine()).startsWith("Content-Length:")) {
                    // Skip headers until Content-Length is found
                }
                contentLength = Integer.parseInt(requestLine.split(": ")[1]);
                
                char[] buffer = new char[contentLength];
                inputStream.read(buffer, 0, contentLength);
                requestBody.append(new String(buffer));
            } else {
                reader.readLine(); // Consume the rest of headers
            }
        }

        String username = extractUsername(requestBody.toString());
        String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
        
        writer.write(responseMessage);
        writer.flush();

        clientSocket.close();
    }

    private static String extractUsername(String requestBody) {
        int startIndex = requestBody.indexOf("username=") + "username=".length();
        int endIndex = requestBody.indexOf("&", startIndex);
        if (endIndex == -1) endIndex = requestBody.length();
        return requestBody.substring(startIndex, endIndex);
    }
}