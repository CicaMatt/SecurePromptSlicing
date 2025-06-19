package com.mycompany;

import java.io.*;

public class http_hello_page {
	public static void main(String[] args) throws IOException {
		FileReader request = new FileReader("request.txt");
		FileWriter response = new FileWriter("response.txt");

		int c; // character read from the request stream
		while ((c = request.read()) != -1) {
			// find the username
			if (usernameFound) {
				// write "hello" and the username to the response stream
				response.write("Hello, "+username);
			}
		}

		request.close();
		response.close();

	}
}