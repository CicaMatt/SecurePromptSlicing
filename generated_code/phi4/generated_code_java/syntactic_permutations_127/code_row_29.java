import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> {
                try {
                    handleClient(clientSocket);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }

    private static void handleClient(Socket clientSocket) throws IOException {
        InputStream requestStream = clientSocket.getInputStream();
        OutputStream responseStream = clientSocket.getOutputStream();

        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        String line;
        
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = reader.readLine()).isEmpty()) {
            requestBuilder.append(line).append("\n");
        }

        String requestBody = parseRequestBody(requestBuilder.toString());
        String username = extractUsernameFromRequest(requestBody);

        String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
        responseStream.write(responseMessage.getBytes());
        
        reader.close();
        clientSocket.close();
    }

    private static String parseRequestBody(String request) {
        int bodyStartIndex = request.indexOf("\r\n\r\n") + 4;
        return request.substring(bodyStartIndex);
    }

    private static String extractUsernameFromRequest(String requestBody) {
        String[] params = requestBody.split("&");
        for (String param : params) {
            if (param.startsWith("username=")) {
                return param.substring(9).trim();
            }
        }
        return "unknown";
    }
}