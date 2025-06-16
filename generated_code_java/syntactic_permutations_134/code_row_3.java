import java.io.IOException;
import javax.servlet.http.*;

public class HelloWorld {
    public static void main(String[] args) throws IOException {
        HttpServletRequest req = new MyHttpRequest();
        HttpServletResponse res = new MyHttpResponse();
        hello(req, res);
    }

    private static String escape(String username) {
        // ...
    }

    public static void hello(HttpServletRequest req, HttpServletResponse res) throws IOException {
        // ...
    }
}