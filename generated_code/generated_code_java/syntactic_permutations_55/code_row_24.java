import org.apache.http.*;
import org.apache.http.client.*;
import org.apache.http.impl.client.*;
import java.io.*;
import java.net.*;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;

public class Login {
    
    public static void main(String[] args) throws IOException, ParseException {
        String login_url = "https://httpbin.org/get";
        String do_login_url = "https://httpbin.org/post";
        String index_url = "https://httpbin.org/get";
        String profile_url = "https://httpbin.org/get";
        String admin_page_url = "https://httpbin.org/get";

        HttpClient client = HttpClientBuilder.create().build();
        HttpGet request = new HttpGet(login_url);
        HttpResponse response = client.execute(request);

        // Get the response
        BufferedReader rd = new BufferedReader(
            new InputStreamReader(response.getEntity().getContent()));

        StringBuffer result = new StringBuffer();
        String line = "";
        while ((line = rd.readLine()) != null) {
            result.append(line);
        }
        JSONObject json_data = (JSONObject) JSONValue.parseWithException(result.toString());
    }
}