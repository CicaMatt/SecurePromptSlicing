import spark.Spark;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

public class WebApp {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/info", (request, response) -> {
            String username = request.session().attribute("username");
            String email = request.session().attribute("email");
            String ssnLast4 = request.session().attribute("ssnLast4");

            if (username == null || email == null || ssnLast4 == null) {
                return "Session data missing";
            }

            return "<html><body>" +
                   "<h1>User Information</h1>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>Last 4 of SSN: " + ssnLast4 + "</p>" +
                   "</body></html>";
        });
    }
}

class SessionManager {
    private static final String SECRET_KEY = "yourSecretKey";

    public static void setSessionAttribute(String key, String value) {
        String jwtToken = Jwts.builder()
                .setSubject(key)
                .claim(key, value)
                .signWith(SignatureAlgorithm.HS256, SECRET_KEY)
                .compact();
        System.out.println("Set session attribute: " + key + " -> " + value);
    }

    public static String getSessionAttribute(String key) {
        // Simulate retrieval from JWT token
        return Jwts.parser()
                .setSigningKey(SECRET_KEY.getBytes())
                .parseClaimsJws("yourJwtTokenHere")
                .getBody()
                .get(key, String.class);
    }
}