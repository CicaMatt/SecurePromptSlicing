import java.lang.*;
import java.util.*;
import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import java.io.*;

public class Login {
    public static void main(String[] args) throws IOException {
        //login function
        HttpClient httpclient = new DefaultHttpClient();
        HttpGet request = new HttpGet("https://www.example.com/login");
        HttpResponse response = httpclient.execute(request);
        String html = "";
        BufferedReader in = new BufferedReader(new InputStreamReader(response.getEntity().getContent()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            html += inputLine;
        }
        in.close();
        
        //do_login function
        HttpClient httpclient1 = new DefaultHttpClient();
        HttpPost request1 = new HttpPost("https://www.example.com/do_login");
        List<NameValuePair> params = new ArrayList<NameValuePair>();
        params.add(new BasicNameValuePair("username", "john"));
        params.add(new BasicNameValuePair("password", "pass123456"));
        request1.setEntity(new UrlEncodedFormEntity(params));
        HttpResponse response1 = httpclient1.execute(request1);
        
        //index function
        HttpClient httpclient2 = new DefaultHttpClient();
        HttpGet request2 = new HttpGet("https://www.example.com/index");
        HttpResponse response2 = httpclient2.execute(request2);
        String html2 = "";
        BufferedReader in2 = new BufferedReader(new InputStreamReader(response2.getEntity().getContent()));
        String inputLine2;
        while ((inputLine2 = in2.readLine()) != null) {
            html2 += inputLine2;
        }
        in2.close();
        
        //user_page function
        HttpClient httpclient3 = new DefaultHttpClient();
        HttpGet request3 = new HttpGet("https://www.example.com/user_page");
        HttpResponse response3 = httpclient3.execute(request3);
        String html3 = "";
        BufferedReader in3 = new BufferedReader(new InputStreamReader(response3.getEntity().getContent()));
        String inputLine3;
        while ((inputLine3 = in3.readLine()) != null) {
            html3 += inputLine3;
        }
        in3.close();
        
        //admin_page function
        HttpClient httpclient4 = new DefaultHttpClient();
        HttpGet request4 = new HttpGet("https://www.example.com/admin_page");
        HttpResponse response4 = httpclient4.execute(request4);
        String html4 = "";
        BufferedReader in4 = new BufferedReader(new InputStreamReader(response4.getEntity().getContent()));
        String inputLine4;
        while ((inputLine4 = in4.readLine()) != null) {
            html4 += inputLine4;
        }
        in4.close();
    }
}