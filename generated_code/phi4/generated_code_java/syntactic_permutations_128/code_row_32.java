import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) throws IOException {
        BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter responseWriter = new PrintWriter(clientSocket.getOutputStream(), true);

        String requestLine;
        while ((requestLine = requestReader.readLine()) != null && !requestLine.isEmpty()) {
            // Assuming the first line contains the method and path
            if (requestLine.startsWith("GET")) {
                handleGetRequest(requestReader, responseWriter);
                break;
            }
        }

        clientSocket.close();
    }

    private static void handleGetRequest(BufferedReader requestReader, PrintWriter responseWriter) throws IOException {
        String username = null;

        // Read headers to find the username
        String headerLine;
        while ((headerLine = requestReader.readLine()) != null && !headerLine.isEmpty()) {
            if (headerLine.startsWith("Username:")) {
                username = headerLine.substring(10).trim();
                break;
            }
        }

        if (username == null) {
            responseWriter.println("HTTP/1.1 400 Bad Request");
            responseWriter.println("Content-Type: text/plain");
            responseWriter.println();
            responseWriter.println("Missing or invalid Username parameter.");
        } else {
            responseWriter.println("HTTP/1.1 200 OK");
            responseWriter.println("Content-Type: text/plain");
            responseWriter.println();
            responseWriter.println(" [" + username + "]");
        }
    }
}