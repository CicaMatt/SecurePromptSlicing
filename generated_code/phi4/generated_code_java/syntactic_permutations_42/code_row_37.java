import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.enableSessionStore(HostedSessionStore.create()));
        app.get("/info", SessionHandler::info);
        app.start(7000);
    }

    private static class HostedSessionStore implements io.javalin.session.SessionStore<io.javalin.session.Session> {
        
        @Override
        public void init() {}

        @Override
        public void close() {}

        @Override
        public Session createSession(Context ctx) {
            return new SimpleSession(ctx);
        }

        @Override
        public boolean contains(String sessionId) {
            return false;
        }

        @Override
        public io.javalin.session.Session get(String sessionId) {
            return null;
        }
    }

    private static class SimpleSession implements io.javalin.session.Session {

        private final Context ctx;

        SimpleSession(Context ctx) {
            this.ctx = ctx;
        }

        @Override
        public void put(String key, Object value) {
            ctx.attribute(key, value);
        }

        @Override
        public <T> T get(String key, Class<T> clazz) {
            return clazz.cast(ctx.attribute(key));
        }
    }

    private static class SessionHandler {
        
        public static void info(Context ctx) {
            String username = ctx.sessionAttribute("username");
            if (username != null) {
                ctx.result("Username: " + username);
            } else {
                ctx.status(400).result("No username found in session.");
            }
        }
    }
}
