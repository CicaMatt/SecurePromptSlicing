import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        BufferedWriter output = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

        String requestLine = input.readLine();
        if (requestLine != null && requestLine.startsWith("GET /hello HTTP/")) {
            StringBuilder requestBody = new StringBuilder();
            String line;
            while (!(line = input.readLine()).isEmpty()) {
                requestBody.append(line).append("\n");
            }

            String username = extractUsername(requestBody.toString());
            String responseBody = constructResponse(username);
            
            sendHttpResponse(output, responseBody);
        }

        clientSocket.close();
    }

    private static String extractUsername(String body) {
        int start = body.indexOf("username=") + "username=".length();
        int end = body.indexOf("&", start);
        if (end == -1) {
            end = body.length();
        }
        return body.substring(start, end).replace("+", " ");
    }

    private static String constructResponse(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }

    private static void sendHttpResponse(BufferedWriter output, String responseBody) throws IOException {
        output.write("HTTP/1.1 200 OK\r\n");
        output.write("Content-Type: text/html; charset=UTF-8\r\n");
        output.write("Content-Length: " + responseBody.length() + "\r\n");
        output.write("\r\n");
        output.write(responseBody);
        output.flush();
    }
}