import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public void http_hello_page(HttpRequest request, HttpResponse response) throws IOException {
        StringBuilder username = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String line;
        while ((line = reader.readLine()) != null) {
            username.append(line);
        }
        reader.close();

        String responseBody = "<html><body><h1>Hello, " + username.toString() + "!</h1></body></html>";
        OutputStream outputStream = response.getOutputStream();
        outputStream.write(responseBody.getBytes());
        outputStream.flush();
        outputStream.close();
    }

    static class HttpRequest {
        private final URL url;
        private final InputStream body;

        public HttpRequest(URL url, InputStream body) {
            this.url = url;
            this.body = body;
        }

        public InputStream getBody() {
            return body;
        }
    }

    static class HttpResponse {
        private final OutputStream outputStream;

        public HttpResponse(OutputStream outputStream) {
            this.outputStream = outputStream;
        }

        public OutputStream getOutputStream() {
            return outputStream;
        }
    }
}