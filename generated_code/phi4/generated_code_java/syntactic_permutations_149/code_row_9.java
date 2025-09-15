import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/database_name";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", Main::insertUserMessageInDb);
        app.get("/", Main::displayMessages);
    }

    public static void insertUserMessageInDb(Context ctx) {
        String message = ctx.formParam("message");
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO messages (content) VALUES (?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, message);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        ctx.redirect("/");
    }

    public static void displayMessages(Context ctx) {
        StringBuilder htmlContent = new StringBuilder("<html><body>");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT content FROM messages";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql);
                 ResultSet rs = pstmt.executeQuery()) {

                while (rs.next()) {
                    String message = rs.getString("content");
                    htmlContent.append("<p>").append(message).append("</p>");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            htmlContent.append("<p>Error retrieving messages.</p>");
        }

        htmlContent.append("</body></html>");
        ctx.result(htmlContent.toString());
    }
}
