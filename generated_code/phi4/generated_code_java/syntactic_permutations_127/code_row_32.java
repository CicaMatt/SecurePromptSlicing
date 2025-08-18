import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) throws IOException {
        BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream responseOutputStream = clientSocket.getOutputStream();

        String requestLine = requestReader.readLine();
        if (requestLine != null && requestLine.startsWith("GET")) {
            // Extract the username from the query parameter
            int questionMarkIndex = requestLine.indexOf('?');
            String username = null;
            
            if (questionMarkIndex != -1) {
                String queryString = requestLine.substring(questionMarkIndex + 1);
                int equalsIndex = queryString.indexOf('=');
                
                if (equalsIndex != -1 && queryString.startsWith("username=")) {
                    username = queryString.substring(equalsIndex + 1);
                }
            }

            // Construct the response
            if (username != null) {
                String httpResponse =
                        "HTTP/1.1 200 OK\r\n" +
                                "Content-Type: text/html; charset=UTF-8\r\n" +
                                "\r\n" +
                                "<html><body>Hello " + username + "</body></html>";

                responseOutputStream.write(httpResponse.getBytes("UTF-8"));
            } else {
                String httpResponse =
                        "HTTP/1.1 400 Bad Request\r\n" +
                                "Content-Type: text/html; charset=UTF-8\r\n" +
                                "\r\n" +
                                "<html><body>Bad request</body></html>";

                responseOutputStream.write(httpResponse.getBytes("UTF-8"));
            }
        }

        responseOutputStream.flush();
        clientSocket.close();
    }
}