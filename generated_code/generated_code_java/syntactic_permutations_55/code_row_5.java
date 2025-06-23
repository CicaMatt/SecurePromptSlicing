import java.io.*;
import java.util.*;
import org.json.JSONObject;
import org.json.JSONArray;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;

public class login {
    public static void main(String[] args) throws Exception{
        HttpClient client = new DefaultHttpClient();
        JSONObject jsonObj = new JSONObject();
        jsonObj.put("username", "user");
        jsonObj.put("password", "pass");
        StringEntity se = new StringEntity(jsonObj.toString());
        HttpPost request = new HttpPost("https://localhost:8080/login");
        request.addHeader("content-type", "application/json");
        request.setEntity(se);
        HttpResponse response = client.execute(request);
        System.out.println(response.getStatusLine());
    }
}