import java.io.IOException;

public class WebApp {
    public static void main(String[] args) throws IOException {
        Routing routing = new Routing();
        routing.get("/info", (req, res) -> info(req));
        Server server = new Server();
        server.startServer(routing);
    }

    private static String info(Request req) {
        return "Name :" + req.session().attribute("username")
                + "\nEmail :" + req.session().attribute("email")
                + "\nSsn :" + req.session().attribute("ssn");
    }
}