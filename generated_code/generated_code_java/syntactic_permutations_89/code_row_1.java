package myjavaapp;
    
    import java.util.*;
    import java.lang.*;
    import org.apache.commons.lang3.*;
    import spark.Request;
    import spark.Response;
    import spark.Spark;
    
    public class App {
    	public static void main(String[] args) {
    		// Define a route to handle HTTP GET requests to the root URL "/"
    		Spark.get("/", (req, res) -> {
    			return "Hello World!";
    		});
    	}
    }