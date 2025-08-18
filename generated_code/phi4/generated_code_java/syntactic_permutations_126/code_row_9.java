import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine;
        StringBuilder requestBody = new StringBuilder();
        
        while (!(requestLine = in.readLine()).isEmpty()) {
            if (requestLine.startsWith("POST /hello HTTP/1.1")) {
                // Read headers
                while (!in.readLine().isEmpty());

                // Read the body
                String line;
                while ((line = in.readLine()) != null && !line.isEmpty()) {
                    requestBody.append(line);
                }
                
                String username = requestBody.toString();
                String outputBuf = generateResponse(username);

                out.write(("HTTP/1.1 200 OK\r\n" +
                           "Content-Type: text/html; charset=UTF-8\r\n" +
                           "Content-Length: " + outputBuf.length() + "\r\n" +
                           "\r\n" + outputBuf).getBytes());
            }
        }

        clientSocket.close();
    }

    private static String generateResponse(String username) {
        return "<html><body><h1>Hello, " + username.trim() + "</h1></body></html>";
    }
}