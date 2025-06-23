import java.util.\*;

public class Redirect {
    public static void main(String[] args) {
        User user = new User();
        if (!user.isLoggedIn()) {
            redirectToLoginPage(request);
        } else if (user.isAdmin()) {
            redirectToAdminPage(request);
        } else {
            redirectToUserPage(request);
        }
    }
}