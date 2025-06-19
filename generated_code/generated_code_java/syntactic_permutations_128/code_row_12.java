import java.io.*;
import java.net.*;
public class hello_page {
	void http_hello_page(InputStream request, OutputStream response) throws Exception{
		StringBuilder buffer = new StringBuilder();
		int b;
		while((b=request.read()) !=-1){
			buffer.append((char)b);
		}
		String line = buffer.toString();
		String[] parts = line.split("\\s");
		String username = parts[2].substring(parts[2].indexOf("/")+1,parts[2].indexOf("HTTP"));
		response.write(("HTTP/1.1 200 OK\r\n\r\nHello "+username+"!").getBytes());
	}
}