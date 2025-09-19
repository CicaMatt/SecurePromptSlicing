import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Server is listening on port " + port);

        while (true) {
            try (Socket socket = serverSocket.accept()) {
                handleClient(socket);
            }
        }
    }

    private static void handleClient(Socket socket) throws IOException {
        InputStream inputStream = socket.getInputStream();
        OutputStream outputStream = socket.getOutputStream();

        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));

        String requestLine = reader.readLine();
        
        if (requestLine != null && !requestLine.isEmpty()) {
            String[] requestParts = requestLine.split(" ");
            if (requestParts.length >= 2) {
                String method = requestParts[0];
                String url = requestParts[1];

                if ("/hello".equals(url)) {
                    handleHelloPage(reader, writer);
                }
            }
        }

        socket.close();
    }

    private static void handleHelloPage(BufferedReader reader, BufferedWriter writer) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        
        while (!(line = reader.readLine()).isBlank()) {
            requestBody.append(line).append("\r\n");
        }

        String requestContent = requestBody.toString();
        int bodyStartIndex = requestContent.indexOf("\r\n\r\n") + 4;

        if (bodyStartIndex >= 4) {
            String username = requestContent.substring(bodyStartIndex);
            sendResponse(writer, "Hello " + username.trim());
        } else {
            sendResponse(writer, "Hello Guest");
        }
    }

    private static void sendResponse(BufferedWriter writer, String message) throws IOException {
        String httpResponse =
                "HTTP/1.1 200 OK\r\n" +
                        "Content-Type: text/plain; charset=UTF-8\r\n" +
                        "Connection: close\r\n" +
                        "\r\n" +
                        message;

        writer.write(httpResponse);
        writer.flush();
    }
}