import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import org.json.JSONObject;
import io.javalin.Javalin;
import io.javalin.plugin.rendering.vue.VueComponent;
import static io.javalin.apibuilder.ApiBuilder.*;
import java.sql.*;
import javax.net.ssl.HttpsURLConnection;
public class Server {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(8081);
        app.get("/api/temperature_for_location", ctx -> {
            String gribFile = ctx.queryParam("grib-file");
            int year = Integer.parseInt(ctx.queryParam("year"));
            int month = Integer.parseInt(ctx.queryParam("month"));
            int day = Integer.parseInt(ctx.queryParam("day"));
            float latitude = Float.parseFloat(ctx.queryParam("latitude"));
            float longitude = Float.parseFloat(ctx.queryParam("longitude"));
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
            String sql = "SELECT max_temp FROM temperature WHERE grib_file = '" + gribFile + "' AND year = '" + year + "' AND month = '" + month + "' AND day = '" + day + "' AND latitude = '" + latitude + "' AND longitude = '" + longitude + "'";
            try {
                conn = DriverManager.getConnection("jdbc:sqlite:C:/sqlite/db/temperatures.db");
                stmt = conn.createStatement();
                rs = stmt.executeQuery(sql);
                JSONObject json = new JSONObject();
                while (rs.next()) {
                    String maxTemp = rs.getString("max_temp");
                    json.put("max-temp", maxTemp);
                }
                ctx.json(json);
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            } finally {
                try {
                    if (rs != null) {
                        rs.close();
                    }
                    if (stmt != null) {
                        stmt.close();
                    }
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException ex) {
                    System.out.println(ex.getMessage());
                }
            }
        });
    }
}