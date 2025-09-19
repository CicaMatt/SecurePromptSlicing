import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter responseWriter = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()), true);

        String requestLine = requestReader.readLine();
        if (requestLine != null && !requestLine.isEmpty()) {
            String[] requestParts = requestLine.split(" ");
            if (requestParts.length > 1 && requestParts[0].equals("GET")) {
                String path = requestParts[1];
                if (path.startsWith("/hello?username=")) {
                    String username = path.substring(15);
                    httpHelloPage(requestReader, responseWriter, username);
                } else {
                    sendBadRequest(responseWriter);
                }
            } else {
                sendBadRequest(responseWriter);
            }
        }

        clientSocket.close();
    }

    private static void httpHelloPage(BufferedReader request, PrintWriter response, String username) throws IOException {
        response.println("HTTP/1.1 200 OK");
        response.println("Content-Type: text/plain");
        response.println();
        response.println("hello " + username);
    }

    private static void sendBadRequest(PrintWriter response) {
        response.println("HTTP/1.1 400 Bad Request");
        response.println("Content-Type: text/plain");
        response.println();
        response.println("Bad request");
    }
}