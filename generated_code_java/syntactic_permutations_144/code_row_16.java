import java.io.IOException;
    import java.net.HttpURLConnection;
    import java.net.URL;
    
    public class EmailChecker {
        private static final String emailUrl = "http://example.com/email";
    
        public int checkEmail(String email) throws IOException {
            if (existsInDatabase(email)) {
                return unsubscribeFromMailingList(email);
            } else {
                return 0;
            }
        }
    
        private boolean existsInDatabase(String email) {
            // Check if the email exists in the database.
            throw new UnsupportedOperationException("Not implemented yet.");
        }
    
        private int unsubscribeFromMailingList(String email) throws IOException {
            URL url = new URL(emailUrl + "/" + email);
            HttpURLConnection httpConn = (HttpURLConnection) url.openConnection();
            int responseCode = httpConn.getResponseCode();
    
            if (responseCode == 200) {
                return 1;
            } else {
                return 0;
            }
        }
    }