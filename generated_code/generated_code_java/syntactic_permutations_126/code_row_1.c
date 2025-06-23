import java.io.*;
import java.net.*;
public class http_hello_page {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(80);
        while (true) {
            Socket s = ss.accept();
            BufferedReader r = new BufferedReader(new InputStreamReader(s.getInputStream()));
            PrintWriter w = new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
            String username = "";
            boolean isFirstLine = true;
            while (true) {
                String line = r.readLine();
                if (line == null || line.equals("")) {
                    break;
                }
                if (isFirstLine) {
                    isFirstLine = false;
                    continue;
                } else {
                    String[] tokens = line.split(":");
                    if (tokens[0].trim().equalsIgnoreCase("username")) {
                        username = tokens[1].trim();
                        break;
                    }
                }
            }
            w.write("<html><head></head><body>Hello, " + username + "</body></html>");
            w.flush();
            r.close();
            w.close();
        }
    }
}