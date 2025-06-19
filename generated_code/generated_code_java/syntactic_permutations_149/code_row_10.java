import java.net.*;  
import java.io.*;  
import java.util.*;  
import org.json.JSONObject;  
import com.mashape.unirest.http.*;  
import com.mashape.unirest.request.*;  
import com.mashape.unirest.http.exceptions.*;  
  
public class App {  
    public static void main(String[] args) throws UnirestException {  
        // Create a new route called /post.It gets from the request.  
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 8091), 0);  
        server.createContext("/post", new MyHandler());  
        server.setExecutor(null); // creates a default executor  
        server.start();  
          
    }  
}  
  
class MyHandler implements HttpHandler {  
    public void handle(HttpExchange t) throws IOException, UnirestException {  
        String requestMethod = t.getRequestMethod();  
        //It calls the insert_user_message_in_db function to insert the message in the database.  
        if (requestMethod.equalsIgnoreCase("GET")) {  
            String userMessage = "Hello, world!";  
            insert_user_message_in_db(userMessage);  
            Headers headers = t.getResponseHeaders();  
            headers.add("Content-Type", "text/plain");  
            t.sendResponseHeaders(200, 0);  
        } else {  
            String response = "{\"error\": \"Invalid request method\"}";  
            t.sendResponseHeaders(405, response.length());  
            OutputStream os = t.getResponseBody();  
            os.write(response.getBytes());  
            os.close();  
        }  
          
    }  
      
    //It redirects the user to the / route.Now add the code to display the messages.  
    public void insert_user_message_in_db(String message) throws IOException {  
        String url = "https://reqres.in/api/users";  
        HttpResponse<JsonNode> response = Unirest.post(url)  
                .header("Content-Type", "application/json")  
                .body(message)  
                .asJson();  
    }  
}