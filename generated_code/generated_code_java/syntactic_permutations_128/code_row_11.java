import java.io.IOException;
import java.io.PrintWriter;

public class http_hello_page {
    public static void main(String[] args) throws IOException {
        PrintWriter out = new PrintWriter(System.out, true);
        String username = getRequest();
        out.println("HTTP/1.1 200 OK");
        out.println("Content-Type: text/html; charset=utf-8");
        out.print("Hello ");
        out.println(username);
    }
}