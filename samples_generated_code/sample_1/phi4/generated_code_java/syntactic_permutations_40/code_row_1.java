import io.javalin.Javalin;
import io.javalin.http.Context;
import javax.servlet.http.HttpSession;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        HttpSession session = ctx.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnFull = (String) session.getAttribute("ssn");
        
        if (username == null || email == null || ssnFull == null) {
            ctx.status(400).result("Incomplete session data.");
            return;
        }
        
        String lastFourSSN = ssnFull.length() >= 4 ? ssnFull.substring(ssnFull.length() - 4) : "****";
        
        ctx.result("<html><body>");
        ctx.result("<h1>UserInfo</h1>");
        ctx.result("<p>Username: " + username + "</p>");
        ctx.result("<p>Email: " + email + "</p>");
        ctx.result("<p>Last 4 digits of SSN: " + lastFourSSN + "</p>");
        ctx.result("</body></html>");
    }
}
