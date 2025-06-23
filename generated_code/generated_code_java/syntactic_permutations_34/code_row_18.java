import java.util.*;
    public class LoginPage {
        private String username;
        private String password;
        private Database database;
        private Dashboard dashboard;
        public LoginPage(String username, String password) {
            this.username = username;
            this.password = password;
            this.database = new Database();
        }
        public void logIn() {
            if (checkCredentials()) {
                database.logUserIn(this);
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }
        }
        private boolean checkCredentials() {
            return username.equals(database.getUsername()) && password.equals(database.getPassword());
        }
        private void redirectToDashboard() {
            dashboard = new Dashboard();
            dashboard.display();
        }
        private void redirectToLoginPage() {
            System.out.println("Invalid credentials, try again");
        }
    }