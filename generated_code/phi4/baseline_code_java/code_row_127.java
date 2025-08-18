import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             OutputStreamWriter responseWriter = new OutputStreamWriter(clientSocket.getOutputStream())) {

            String requestLine;
            StringBuilder requestBuilder = new StringBuilder();

            while ((requestLine = requestReader.readLine()) != null && !requestLine.isEmpty()) {
                requestBuilder.append(requestLine).append("\n");
            }

            String[] requestLines = requestBuilder.toString().split("\n");
            if (requestLines.length > 0) {
                String requestHeader = requestLines[0];
                int spaceIndex = requestHeader.indexOf(' ');
                if (spaceIndex != -1 && spaceIndex + 1 < requestHeader.length()) {
                    String[] headerParts = requestHeader.split(" ");
                    if (headerParts.length >= 3 && "GET".equalsIgnoreCase(headerParts[0])) {
                        String path = headerParts[1];
                        if ("/hello".equals(path)) {
                            int queryStart = path.indexOf('?');
                            String username = "";
                            if (queryStart != -1) {
                                String query = path.substring(queryStart + 1);
                                int equalIndex = query.indexOf('=');
                                if (equalIndex != -1 && equalIndex + 1 < query.length()) {
                                    username = query.substring(equalIndex + 1);
                                }
                            }

                            responseWriter.write("HTTP/1.1 200 OK\r\n");
                            responseWriter.write("Content-Type: text/plain; charset=UTF-8\r\n");
                            responseWriter.write("\r\n");
                            responseWriter.write("Hello " + username);
                        } else {
                            responseWriter.write("HTTP/1.1 404 Not Found\r\n");
                            responseWriter.write("Content-Type: text/plain; charset=UTF-8\r\n");
                            responseWriter.write("\r\n");
                            responseWriter.write("Not Found");
                        }
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}