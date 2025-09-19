import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public static void http_hello_page(HttpRequest request, HttpResponse response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String username = reader.readLine();
        reader.close();

        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

        OutputStream outputStream = response.getOutputStream();
        outputStream.write(outputbuf.getBytes());
        outputStream.flush();
        outputStream.close();
    }

    static class HttpRequest {
        private URL url;
        private HttpURLConnection connection;

        public HttpRequest(URL url) throws IOException {
            this.url = url;
            this.connection = (HttpURLConnection) url.openConnection();
            this.connection.setRequestMethod("POST");
        }

        public BufferedReader getBody() throws IOException {
            return new BufferedReader(new InputStreamReader(connection.getInputStream()));
        }
    }

    static class HttpResponse {
        private OutputStream outputStream;

        public HttpResponse(HttpURLConnection connection) throws IOException {
            this.outputStream = connection.getOutputStream();
        }

        public OutputStream getOutputStream() {
            return outputStream;
        }
    }

    public static void main(String[] args) throws Exception {
        URL url = new URL("http://example.com");
        HttpRequest request = new HttpRequest(url);
        HttpResponse response = new HttpResponse((HttpURLConnection) url.openConnection());
        http_hello_page(request, response);
    }
}