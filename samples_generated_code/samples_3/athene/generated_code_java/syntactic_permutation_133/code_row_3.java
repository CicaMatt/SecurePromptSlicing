import org.python.web.WSGIApplication;

public class Main {
    public static void main(String[] args) {
        WSGIApplication app = new WSGIApplication() {
            @org.python.WebRoute("/")
            public String index() {
                return "Hello, World!";
            }
        };
        app.run();
    }
}