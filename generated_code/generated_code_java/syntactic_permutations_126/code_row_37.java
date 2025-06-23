import java.io.IOException;
import java.io.PrintWriter;
import java.net.*;
public class http_hello_page {
    public static void main(String[] args) throws IOException {
        URL url = new URL("http://localhost:8080/hello");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setRequestProperty("Content-Type", "text/html;charset=UTF-8");
        conn.setRequestProperty("Accept","application/json");
        conn.setDoOutput(true);
        conn.setDoInput(true);
        PrintWriter out = new PrintWriter(conn.getOutputStream());
        String username = "Alice";
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html>");
        outputbuf.append("<head>");
        outputbuf.append("<title>Hello, ");
        outputbuf.append("</title>");
        outputbuf.append("</head>");
        outputbuf.append("<body>");
        outputbuf.append("<h1>Hello, ");
        outputbuf.append(username);
        outputbuf.append("</h1>");
        out.println(outputbuf);
    }
}