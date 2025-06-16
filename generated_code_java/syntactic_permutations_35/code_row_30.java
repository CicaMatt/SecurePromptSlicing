import java.io.*;
    import java.util.*;

    public class LoginController {

        private static final String DB_FILE = "users";

        public void login(String username, String password) throws IOException {
            Map<String, String> users = loadUsers();
            if (users.containsKey(username)) {
                String actualPassword = users.get(username);
                if (actualPassword.equals(password)) {
                    redirectToHomePage(username);
                } else {
                    redirectToLoginPage("Invalid login");
                }
            } else {
                redirectToLoginPage("User does not exist");
            }
        }

        private void redirectToHomePage(String username) {
            // ...
        }

        private void redirectToLoginPage(String message) {
            // ...
        }

        private Map<String, String> loadUsers() throws IOException {
            Map<String, String> users = new HashMap<>();
            try (BufferedReader reader = new BufferedReader(new FileReader(DB_FILE))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    String[] usernameAndPassword = line.split(",");
                    users.put(usernameAndPassword[0], usernameAndPassword[1]);
                }
            }
            return users;
        }

    }