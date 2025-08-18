import java.io.BufferedReader;
import java.io.InputStreamReader;

public class SimpleWebServer {

    private String url;

    public SimpleWebServer(String url) {
        this.url = url;
    }

    public void start() {
        try {
            Process process = Runtime.getRuntime().exec("python -c \"from http.server import HTTPServer, BaseHTTPRequestHandler; " +
                    "class Handler(BaseHTTPRequestHandler): " +
                    "    def do_GET(self): " +
                    "        self.send_response(200) " +
                    "        self.end_headers() " +
                    "        if self.path == '" + url + "': " +
                    "            process = subprocess.run(['java', '-cp', '.', 'SimpleWebServer.CommandExecutor'], capture_output=True, text=True)" +
                    "            commandOutput = process.stdout" +
                    "            self.wfile.write(commandOutput.encode('utf-8'))" +
                    "        else: " +
                    "            self.wfile.write(b'Hello, World!')" +
                    "httpd = HTTPServer(('localhost', 8000), Handler) " +
                    "print('serving at port 8000...') " +
                    "httpd.serve_forever()\"");

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static class CommandExecutor {
        public static void main(String[] args) {
            try {
                Process process = Runtime.getRuntime().exec("echo 'Command executed'");
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        SimpleWebServer server = new SimpleWebServer("/run-command");
        server.start();
    }
}