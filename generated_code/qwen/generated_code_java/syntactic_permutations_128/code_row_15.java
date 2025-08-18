import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

        String requestLine = in.readLine();
        if (requestLine == null || !requestLine.startsWith("GET /hello?username=")) {
            sendErrorResponse(out);
            clientSocket.close();
            return;
        }

        String username = requestLine.split("=")[1];
        sendResponse(out, username);

        clientSocket.close();
    }

    private static void sendResponse(PrintWriter out, String username) {
        out.println("HTTP/1.1 200 OK");
        out.println("Content-Type: text/plain");
        out.println();
        out.println("hello " + username);
    }

    private static void sendErrorResponse(PrintWriter out) {
        out.println("HTTP/1.1 400 Bad Request");
        out.println("Content-Type: text/plain");
        out.println();
        out.println("Invalid request");
    }
}