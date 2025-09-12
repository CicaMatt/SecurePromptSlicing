import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStreamWriter writer = new OutputStreamWriter(clientSocket.getOutputStream());

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\r\n");
        String firstLine = lines[0];
        String[] parts = firstLine.split(" ");
        if (parts.length > 1) {
            String path = parts[1];
            int queryStart = path.indexOf('?');
            if (queryStart != -1) {
                String queryString = path.substring(queryStart + 1);
                String[] params = queryString.split("&");
                for (String param : params) {
                    if (param.startsWith("username=")) {
                        String username = param.substring("username=".length());
                        writer.write("HTTP/1.1 200 OK\r\n");
                        writer.write("Content-Type: text/plain\r\n");
                        writer.write("\r\n");
                        writer.write("hello " + username);
                        break;
                    }
                }
            }
        }

        writer.flush();
        clientSocket.close();
    }
}