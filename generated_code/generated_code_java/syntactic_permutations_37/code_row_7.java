import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import com.auth0.jwt.JWT;
import com.auth0.jwt.exceptions.AlgorithmMismatchException;
import com.auth0.jwt.exceptions.SignatureVerificationException;
import com.auth0.jwt.exceptions.TokenExpiredException;
import com.auth0.jwt.interfaces.DecodedJWT;
import java.security.*;

@WebServlet(name = "Login", urlPatterns = { "/login" })
public class Login extends HttpServlet {
    private String tokenSecret = "<YOUR_TOKEN_SECRET>"; // Your secret here!

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
            String authorizationHeader = request.getHeader("Authorization");
            if (authorizationHeader == null || !authorizationHeader.startsWith("Bearer ")) {
                response.sendRedirect("/cant_login?error=Not+logged+in.");
                return;
            }

            String idToken = authorizationHeader.substring(7);
            DecodedJWT jwt = JWT.decode(idToken);
            if (jwt.getAlgorithm() != "HS256") {
                throw new AlgorithmMismatchException("This token has an invalid algorithm.");
            }
            if (!jwt.verify(this.tokenSecret)) {
                throw new SignatureVerificationException("Invalid token signature");
            }
            if (jwt.isExpired()) {
                throw new TokenExpiredException("The specified token is expired.");
            }

            response.sendRedirect("/success");
        } catch (AlgorithmMismatchException | SignatureVerificationException | TokenExpiredException ex) {
            response.sendRedirect("/cant_login?error=" + ex.getMessage());
        }
    }
}