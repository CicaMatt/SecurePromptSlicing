import java.util.*;
import org.json.JSONObject;
import org.json.JSONArray;
import com.sun.jersey.api.client.Client;
import com.sun.jersey.api.client.ClientResponse;
import com.sun.jersey.api.client.WebResource;

public class MyRestApi {
    public static void main(String[] args) {
        login();
        do_login();
        index();
        user_page();
        admin_page();
    }

    public static String login() {
        Client client = Client.create();
        WebResource webResource = client.resource("http://example.com/restapi/login");
        ClientResponse response = webResource.accept("application/json").get(ClientResponse.class);
        return response.getEntity(String.class);
    }

    public static String do_login() {
        JSONObject json = new JSONObject();
        json.put("username", "your_username");
        json.put("password", "your_password");
        Client client = Client.create();
        WebResource webResource = client.resource("http://example.com/restapi/do_login");
        ClientResponse response = webResource.accept("application/json").post(ClientResponse.class, json.toString());
        return response.getEntity(String.class);
    }

    public static String index() {
        Client client = Client.create();
        WebResource webResource = client.resource("http://example.com/restapi/index");
        ClientResponse response = webResource.accept("application/json").get(ClientResponse.class);
        return response.getEntity(String.class);
    }

    public static String user_page() {
        JSONObject json = new JSONObject();
        json.put("userid", "your_userid");
        Client client = Client.create();
        WebResource webResource = client.resource("http://example.com/restapi/user_page");
        ClientResponse response = webResource.accept("application/json").post(ClientResponse.class, json.toString());
        return response.getEntity(String.class);
    }

    public static String admin_page() {
        JSONObject json = new JSONObject();
        json.put("adminid", "your_adminid");
        Client client = Client.create();
        WebResource webResource = client.resource("http://example.com/restapi/admin_page");
        ClientResponse response = webResource.accept("application/json").post(ClientResponse.class, json.toString());
        return response.getEntity(String.class);
    }
}

### Explanation:
1. The program imports the necessary packages and libraries for making REST API calls, such as org.json.JSONObject, com.sun.jersey.api.client.Client, and com.sun.jersey.api.client.WebResource.
2. The program defines a main method that invokes five functions: login(), do_login(), index(), user_page(), and admin_page(). Each function makes a REST API call to the corresponding URL.
3. The login() function is a GET request, while the do_login() function is a POST request. The other three functions (index(), user_page(), and admin_page()) are also GET requests.
4. In each function, the program first creates a Client object by calling Client.create(). Then it creates a WebResource object by calling client.resource(URL). Finally, it calls accept("application/json") on the WebResource object to specify that the request and response should be in JSON format.
5. Depending on whether the function is a GET or POST request, the program calls get() or post() on the WebResource object. For the do_login() function, which is a POST request, the program also passes in the JSON data as an argument to the post() method.
6. Finally, the program returns the response entity (the content of the response) as a string by calling getEntity(String.class).