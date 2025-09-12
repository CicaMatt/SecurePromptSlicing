import io.javalin.Javalin;
import io.javalin.http.Context;
import io.javalin.session.Session;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.enableSessionStore(new MemorySessionStore())).start(7000);

        app.get("/info", ctx -> {
            Session session = ctx.getSession();
            String username = (String) session.attribute("username");
            String email = (String) session.attribute("email");
            String ssn = (String) session.attribute("ssn");

            String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            ctx.result(response);
        });
    }

    // MemorySessionStore implementation
    import io.javalin.session.SessionHandler;

    public static class MemorySessionStore implements SessionHandler {
        private final java.util.Map<String, Session> sessions = new java.util.concurrent.ConcurrentHashMap<>();

        @Override
        public void sessionCreated(String sessionId, Context ctx) {
            sessions.put(sessionId, new Session());
        }

        @Override
        public void sessionExpired(String sessionId) {
            sessions.remove(sessionId);
        }

        @Override
        public Session getSession(String sessionId) {
            return sessions.get(sessionId);
        }
    }
}