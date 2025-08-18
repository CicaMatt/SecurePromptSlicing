import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

        String line;
        StringBuilder requestBuilder = new StringBuilder();

        while ((line = in.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\\r?\\n");

        for (String header : lines) {
            if (header.startsWith("GET /hello?username=")) {
                String username = header.substring(21);
                sendResponse(out, username);
                break;
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }

    private static void sendResponse(BufferedWriter out, String username) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/html\r\n" +
                          "\r\n" +
                          "<html><body><h1>Hello " + username + "</h1></body></html>";

        out.write(response);
        out.flush();
    }
}