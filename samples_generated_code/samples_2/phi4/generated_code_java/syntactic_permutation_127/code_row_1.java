import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpServerExample {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String inputLine;
        StringBuilder requestBody = new StringBuilder();

        while ((inputLine = reader.readLine()) != null) {
            requestBody.append(inputLine);
        }

        // Extract username from the request. Assuming it's a simple POST request with form data.
        String contentType = request.getContentType();
        if (contentType == null || !contentType.startsWith("application/x-www-form-urlencoded")) {
            response.write(("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n" + "Invalid content type").getBytes());
            return;
        }

        String[] parts = requestBody.toString().split("&");
        for (String part : parts) {
            String[] keyValue = part.split("=");
            if ("username".equals(keyValue[0])) {
                String username = keyValue.length > 1 ? new String(java.util.Base64.getDecoder().decode(keyValue[1].trim())).replace('+', ' ').replace('/', '_') : "";
                String httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
                response.write(httpResponse.getBytes());
                return;
            }
        }

        response.write(("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n" + "Username not provided").getBytes());
    }

    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost:8080/hello");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setDoOutput(true);
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

        String postData = "username=JohnDoe";
        try (OutputStream os = connection.getOutputStream()) {
            byte[] input = postData.getBytes("utf-8");
            os.write(input, 0, input.length);
        }

        InputStream responseStream = connection.getInputStream();
        http_hello_page(responseStream, connection.getOutputStream());
    }
}