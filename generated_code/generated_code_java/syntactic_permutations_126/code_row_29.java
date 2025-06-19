package com.example.hello;

import java.io.*;
import java.net.*;

public class Hello {

	private static final int PORT = 8080;

	public static void main(String[] args) {
		try {
			ServerSocket serverSocket = new ServerSocket(PORT);
			System.out.println("The server is running on port " + PORT);

			while (true) {
				// Wait for a client to connect to the server
				Socket socket = serverSocket.accept();

				HttpURLConnection conn = (HttpURLConnection) url.openConnection();
				conn.setDoOutput(true);
				conn.setRequestMethod("GET");

				try {
					http_hello_page(socket, socket.getInputStream(), socket.getOutputStream());
				} catch (IOException e) {
					System.out.println("Error reading/writing to the client: " + e.getMessage());
					continue;
				}

				// Close the socket for the current client
				socket.close();
			}
		} catch (IOException e) {
			System.out.println("Error starting server: " + e.getMessage());
		}
	}

	private static void http_hello_page(Socket socket, InputStream inputStream, OutputStream outputStream) throws IOException {
		String username = readUsername(inputStream);
		String outputbuf = buildHTMLPage(username);
		writeToResponseStream(outputStream, outputbuf);
		closeResponseStream(outputStream);
	}

	private static String readUsername(InputStream inputStream) throws IOException {
		String username;
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
		username = bufferedReader.readLine();
		return username;
	}

	private static String buildHTMLPage(String username) {
		return "<html>\n" +
			"  <head><title>Hello Page</title></head>\n" +
			"  <body>\n" +
			"    <h1>" + username + ", Hello!</h1>\n" +
			"  </body>\n" +
			"</html>";
	}

	private static void writeToResponseStream(OutputStream outputStream, String outputbuf) throws IOException {
		PrintWriter printWriter = new PrintWriter(outputStream);
		printWriter.write(outputbuf);
		printWriter.flush();
	}

	private static void closeResponseStream(OutputStream outputStream) throws IOException {
		outputStream.close();
	}

}