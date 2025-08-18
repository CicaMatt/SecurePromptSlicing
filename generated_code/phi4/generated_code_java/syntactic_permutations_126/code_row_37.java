import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server started on port 8080");

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
            BufferedReader input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream output = clientSocket.getOutputStream();
        ) {
            String requestLine;
            while (!(requestLine = input.readLine()).isEmpty()) {
                if (requestLine.startsWith("GET /hello")) {
                    String requestBody = readRequestBody(input);
                    String username = extractUsername(requestBody);
                    String responseBody = constructResponse(username);
                    sendHttpResponse(output, responseBody);
                    break;
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

    private static String readRequestBody(BufferedReader input) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while (!(line = input.readLine()).isEmpty()) {
            requestBody.append(line).append("\r\n");
        }
        return requestBody.toString();
    }

    private static String extractUsername(String requestBody) {
        String[] lines = requestBody.split("\r\n");
        for (String line : lines) {
            if (line.startsWith("username=")) {
                return line.substring(9);
            }
        }
        return "Guest";
    }

    private static String constructResponse(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }

    private static void sendHttpResponse(OutputStream output, String responseBody) throws IOException {
        String httpResponse =
            "HTTP/1.1 200 OK\r\n" +
            "Content-Type: text/html; charset=UTF-8\r\n" +
            "Content-Length: " + responseBody.length() + "\r\n\r\n" +
            responseBody;

        output.write(httpResponse.getBytes("UTF-8"));
        output.flush();
    }
}