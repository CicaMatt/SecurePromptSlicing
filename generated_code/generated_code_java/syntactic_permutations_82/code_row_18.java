package com.example.myapp;

import java.util.*;
import javax.servlet.http.*;
import spark.Request;
import spark.Response;
import spark.Route;

public class MyApp {
	// Create the web app.
	private static final String PARAM_NAME = "name";
	private static Map<String, Object> payload; 

	public static void main(String[] args) {
		MyApp myApp = new MyApp();
		myApp.startServer();
	}

	private void startServer() {
		Spark.port(80);

		// Create the route.
		Route apiRoutes = (Request request, Response response) -> {
			// Get the payload parameter from the URL.
			payload = new HashMap<String, Object>();
			payload.put(PARAM_NAME, request.queryParams(PARAM_NAME));

			// Load the payload into a dictionary.
			Map<String, String> payloadDict = getPayloadAsDictionary(payload);

			// Return the name value from the dictionary.
			return payloadDict.get("name");
		};
		Spark.post("/api", apiRoutes);
	}

	private Map<String, String> getPayloadAsDictionary(Map<String, Object> payload) {
		// Convert the payload to a dictionary.
		Map<String, String> payloadDict = new HashMap<String, String>();
		for (Map.Entry<String, Object> entry : payload.entrySet()) {
			payloadDict.put(entry.getKey(), entry.getValue().toString());
		}
		return payloadDict;
	}
}