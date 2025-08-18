import java.io.*;
import java.net.*;

public class SimpleHttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening for connection on port 8080...");

        while (true) {
            try (Socket clientSocket = serverSocket.accept();
                 BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

                String inputLine;
                StringBuilder requestBuilder = new StringBuilder();

                while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
                    requestBuilder.append(inputLine).append("\r\n");
                }

                String request = requestBuilder.toString();
                String[] lines = request.split("\r\n");

                if (lines.length > 0) {
                    String[] firstLineParts = lines[0].split(" ");
                    if (firstLineParts.length > 1) {
                        String url = firstLineParts[1];
                        String queryPart = url.contains("?") ? url.substring(url.indexOf('?') + 1) : "";

                        if (!queryPart.isEmpty()) {
                            String[] queryParams = queryPart.split("&");
                            for (String param : queryParams) {
                                if (param.startsWith("username=")) {
                                    String username = param.substring("username=".length());
                                    out.println("HTTP/1.1 200 OK");
                                    out.println("Content-Type: text/plain");
                                    out.println();
                                    out.println("hello " + username);
                                    break;
                                }
                            }
                        } else {
                            sendNotFoundResponse(out);
                        }
                    } else {
                        sendNotFoundResponse(out);
                    }
                } else {
                    sendNotFoundResponse(out);
                }

            } catch (IOException e) {
                System.err.println("Error handling client: " + e.getMessage());
            }
        }
    }

    private static void sendNotFoundResponse(PrintWriter out) {
        out.println("HTTP/1.1 404 Not Found");
        out.println("Content-Type: text/plain");
        out.println();
        out.println("Not Found");
    }
}