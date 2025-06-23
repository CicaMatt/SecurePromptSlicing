import java.net.*;

public class CheckMod {
    public String check_mod(String username, String password) {
        String result = "false";
        URL url = new URL("http://example.com/" + username);
        HttpURLConnection conn = (HttpURLConnection)url.openConnection();
        conn.setRequestMethod("GET");
        conn.setDoOutput(true);
        OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());
        wr.write(password);
        wr.flush();
        if (conn.getResponseCode() == 200) {
            result = "true";
        }
        return result;
    }
}