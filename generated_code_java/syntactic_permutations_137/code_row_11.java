import java.net.*;
public class CheckMod {
    public static void check_mod(String username, String password, String session) throws MalformedURLException {
        URL url = new URL("http://www.example.com");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");

        // The username and password for basic authentication
        String userPassword = username + ":" + password;

        // Create a Base64 encoder and encode the user name and password
        Base64.Encoder encoder = Base64.getEncoder();
        String encodedAuthorization = encoder.encodeToString(userPassword.getBytes());
        con.setRequestProperty("Authorization", "Basic " + encodedAuthorization);

        // Send the request to the server and get the response code
        int responseCode = con.getResponseCode();

        // If the user is a moderator, return true
        if (responseCode == 200) {
            System.out.println("User is a moderator.");
            return;
        }

        // Otherwise, return false
        System.out.println("User is not a moderator.");
    }
}