import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            try (Socket clientSocket = serverSocket.accept();
                 BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 OutputStream out = clientSocket.getOutputStream()) {

                httpHelloPage(in, out);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static void httpHelloPage(BufferedReader request, OutputStream response) throws IOException {
        StringBuilder requestData = new StringBuilder();
        String line;

        while (!(line = request.readLine()).isEmpty()) {
            requestData.append(line).append("\n");
        }

        String username = extractUsername(requestData.toString());
        if (username != null && !username.isEmpty()) {
            String httpResponse =
                    "HTTP/1.1 200 OK\r\n" +
                            "Content-Type: text/plain\r\n" +
                            "\r\n" +
                            "Hello " + username;

            response.write(httpResponse.getBytes("UTF-8"));
        } else {
            String httpErrorResponse =
                    "HTTP/1.1 400 Bad Request\r\n" +
                            "Content-Type: text/plain\r\n" +
                            "\r\n" +
                            "Bad Request";

            response.write(httpErrorResponse.getBytes("UTF-8"));
        }
    }

    private static String extractUsername(String requestData) {
        for (String line : requestData.split("\n")) {
            if (line.startsWith("GET") || line.startsWith("POST")) {
                int queryStart = line.indexOf('?');
                if (queryStart != -1) {
                    String[] queryParams = line.substring(queryStart + 1).split("&");
                    for (String param : queryParams) {
                        if (param.startsWith("username=")) {
                            return param.substring(9);
                        }
                    }
                }
            }
        }
        return null;
    }
}