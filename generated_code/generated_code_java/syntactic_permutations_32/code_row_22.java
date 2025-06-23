package com.example;

import spark.Spark.*;

public class App {
	static String URL = "https://www.example.com";
	
	static boolean redirect_invalid_url(String url) {
		return url.contains("example.com");
	}

	public static void main(String[] args) {
		port(8080);
		get("/redirect/:url", (req, res) -> {
			if(redirect_invalid_url(req.params(":url"))) {
				return "Invalid URL";
			}
			else {
				res.redirect(URL);
				return null;
			}
		});
	}
	
}