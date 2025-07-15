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
