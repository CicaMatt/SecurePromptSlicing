import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class HttpServer {

    public static void http_hello_page(BufferedReader request, PrintWriter response) throws IOException {
        String inputLine;
        StringBuilder requestBody = new StringBuilder();
        
        while ((inputLine = request.readLine()) != null && !inputLine.isEmpty()) {
            requestBody.append(inputLine).append("\n");
        }
        
        if (requestBody.length() > 0) {
            String[] headers = requestBody.toString().split("\r\n\r\n", 2);
            String body = headers[1].trim();
            
            int contentLengthIndex = -1;
            for (int i = 0; i < headers[0].split("\r\n").length; i++) {
                if (headers[0].split("\r\n")[i].startsWith("Content-Length:")) {
                    contentLengthIndex = i;
                    break;
                }
            }
            
            String username = "";
            if (contentLengthIndex != -1) {
                int contentLength = Integer.parseInt(headers[0].split("\r\n")[contentLengthIndex].split(": ")[1]);
                if (body.length() >= contentLength) {
                    username = body.substring(0, contentLength);
                }
            }

            response.println("HTTP/1.1 200 OK");
            response.println("Content-Type: text/html; charset=utf-8");
            response.println();
            
            response.printf("<html><head><title>Hello Page</title></head>" +
                    "<body><h1>Hello %s!</h1></body></html>", username);
        }
    }

    public static void main(String[] args) throws IOException {
        // Simulating client request
        String clientRequest = "POST / HTTP/1.1\r\n" +
                "Host: localhost\r\n" +
                "Content-Type: application/x-www-form-urlencoded\r\n" +
                "Content-Length: 8\r\n" +
                "\r\n" +
                "username";

        BufferedReader request = new BufferedReader(new InputStreamReader(clientRequest.getBytes()));
        PrintWriter response = new PrintWriter(new OutputStreamWriter(System.out));

        http_hello_page(request, response);

        response.flush();
    }
}