import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleHttpServer {

    private static final int PORT = 8080;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream()
        ) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            String requestLine = reader.readLine();
            if (requestLine != null && requestLine.startsWith("GET /hello")) {
                handleHelloPage(reader, output);
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

    private static void handleHelloPage(BufferedReader reader, OutputStream output) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line).append("\n");
        }

        String username = parseUsername(requestBody.toString());
        String responseBody = generateHelloPage(username);

        sendHttpResponse(output, 200, "OK", "text/html", responseBody);
    }

    private static String parseUsername(String request) {
        int pos = request.indexOf("username=");
        if (pos != -1) {
            pos += "username=".length();
            int endPos = request.indexOf("&", pos);
            if (endPos == -1) {
                return request.substring(pos);
            }
            return request.substring(pos, endPos);
        }
        return "Guest";
    }

    private static String generateHelloPage(String username) {
        return "<html><body><h1>Hello, " + username + "</h1></body></html>";
    }

    private static void sendHttpResponse(OutputStream output, int statusCode, String statusMessage, String contentType, String responseBody) throws IOException {
        PrintWriter writer = new PrintWriter(output, true);
        writer.println("HTTP/1.1 " + statusCode + " " + statusMessage);
        writer.println("Content-Type: " + contentType);
        writer.println("Content-Length: " + responseBody.length());
        writer.println();
        writer.print(responseBody);
    }
}