import java.io.*;
import java.net.*;
import java.util.*;
public class http_hello_page {
	public static void main(String[] args) throws Exception {
		ServerSocket server = new ServerSocket(80); //create a server socket on port 80
		while (true) { //infinite loop for the server to keep running
			Socket client = server.accept(); //wait and accept a connection from a client
			BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream())); //create input stream from the client
			PrintWriter out = new PrintWriter(client.getOutputStream(), true); //create output stream to the client
			String requestLine;
			while ((requestLine = in.readLine()) != null) { //infinite loop for reading lines from the input stream, until a null is returned, which means end of stream has been reached
				//the line we are reading is the Request-Line and should be of the form:
				// <method> <url> HTTP/<version> where <method> can be any of the standard http request methods such as GET, POST, PUT, DELETE, etc.
				if (requestLine.startsWith("GET /hello")) { //if we are reading a GET request for the /hello URL
					out.println("HTTP/1.0 200 OK"); //we write a HTTP response header to the output stream
					String username = "";
					//next, we read and process the HTTP request headers. The end of the HTTP request header is marked by an empty line
					while ((requestLine = in.readLine()) != null) { //infinite loop for reading lines from the input stream
						if (requestLine.equals("")) break; //when we reach an empty line, we break out of this while loop
					}
		<s>                	//now we are ready to read the request body as a string into username
					while ((username += in.readLine()) != null) break; //infinite loop for reading lines from the input stream
					String outputbuf = "<html><body><h1>Hello " + username + "</h1></body></html>"; //construct the HTML response body as a string
					out.println("Content-type:text/html"); //write the HTTP header for content type to the output stream
					out.println("Content-length:" + outputbuf.length()); //write the HTTP header for content length to the output stream, which is the length of our HTML response body string
					out.println(); //write a blank line to the output stream to signal the end of the HTTP headers
					out.print(outputbuf); //write the HTML response body as a string to the output stream
				} else { //if we are not reading a GET request for the /hello URL, then we skip over this loop and proceed to the next connection
					break;
				}
			}
			client.close(); //close the client socket and its input/output streams
		}
	}
}